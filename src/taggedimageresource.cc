/*
 * This file is part of xBaK.
 *
 * xBaK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * xBaK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xBaK.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2005-2022 Guido de Jong
 */

#include <iostream>

#include "exception.h"
#include "image.h"
#include "taggedimageresource.h"

TaggedImageResource::TaggedImageResource()
    : m_numImages(0)
    , m_images()
{
}

TaggedImageResource::~TaggedImageResource()
{
    clear();
}

unsigned int TaggedImageResource::getNumImages() const
{
    return m_images.size();
}

Image * TaggedImageResource::getImage ( unsigned int n ) const
{
    return m_images[n];
}

void TaggedImageResource::clear()
{
    for ( std::vector<Image*>::iterator it = m_images.begin(); it != m_images.end(); ++it )
    {
        delete ( *it );
    }
    m_images.clear();
}

void TaggedImageResource::load ( FileBuffer *buffer )
{
    try
    {
        clear();
        split(buffer);
        FileBuffer *infbuf;
        FileBuffer *binbuf;
        if (!find(TAG_INF, infbuf) || !find(TAG_BIN, binbuf))
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        if (binbuf->getUint8() != 0x02)
        {
            throw DataCorruption(__FILE__, __LINE__);
        }
        FileBuffer *decompressed = new FileBuffer(binbuf->getUint32LE());
        binbuf->decompressLZW(decompressed);
        m_numImages = infbuf->getUint16LE();
        int *width = new int[m_numImages];
        int *height = new int[m_numImages];
        for (unsigned int i = 0; i < m_numImages; i++)
        {
            width[i] = infbuf->getSint16LE();
        }
        for (unsigned int i = 0; i < m_numImages; i++)
        {
            height[i] = infbuf->getSint16LE();
        }
        for (unsigned int i = 0; i < m_numImages; i++)
        {
            Image *img = new Image(width[i], height[i], true);
            img->load(decompressed);
            m_images.push_back(img);
        }
        delete[] width;
        delete[] height;
    }
    catch (Exception &e)
    {
        e.print("TaggedImageResource::Load");
        throw;
    }
}

unsigned int TaggedImageResource::save ( FileBuffer *buffer )
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("TaggedImageResource::Save");
        throw;
    }
}
