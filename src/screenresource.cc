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

#include "exception.h"
#include "screenresource.h"

ScreenResource::ScreenResource()
    : m_image(0)
{
}

ScreenResource::~ScreenResource()
{
    clear();
}

Image * ScreenResource::getImage()
{
    return m_image;
}

void ScreenResource::clear()
{
    if (m_image)
    {
        delete m_image;
        m_image = 0;
    }
}

void ScreenResource::load(FileBuffer *buffer)
{
    try
    {
        bool isBookScreen = false;
        clear();
        if (buffer->getUint16LE() != 0x27b6)
        {
            buffer->rewind();
            isBookScreen = true;
        }
        if (buffer->getUint8() != 0x02)
        {
            throw DataCorruption(__FILE__, __LINE__);
        }
        FileBuffer *decompressed = new FileBuffer(buffer->getUint32LE());
        buffer->decompressLZW(decompressed);
        m_image = isBookScreen ? new Image(BOOK_SCREEN_WIDTH, BOOK_SCREEN_HEIGHT, true) : new Image(SCREEN_WIDTH, SCREEN_HEIGHT);
        m_image->load(decompressed);
        delete decompressed;
    }
    catch (Exception &e)
    {
        e.print("ScreenResource::Load");
        throw;
    }
}

unsigned int ScreenResource::save(FileBuffer *buffer)
{
    try
    {
        //buffer->PutUint16LE(0x27b6);
        buffer->putUint8(0x02);
        FileBuffer *decompressed = new FileBuffer(SCREEN_WIDTH * SCREEN_HEIGHT);
        unsigned int size = m_image->save(decompressed);
        buffer->putUint32LE(size);
        FileBuffer *compressed = new FileBuffer(size);
        decompressed->rewind();
        size = decompressed->compressLZW(compressed);
        compressed->rewind();
        buffer->copyFrom(compressed, size);
        delete compressed;
        delete decompressed;
        return size;
    }
    catch (Exception &e)
    {
        e.print("ScreenResource::Save");
        throw;
    }
}
