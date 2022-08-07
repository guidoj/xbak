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
#include "fontresource.h"
#include "mediatoolkit.h"

FontResource::FontResource()
    : TaggedResource()
    , m_font(0)
{}

FontResource::~FontResource()
{
    clear();
}

Font*
FontResource::getFont() const
{
    return m_font;
}

void
FontResource::clear()
{
    delete m_font;
}

void
FontResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        split(buffer);
        FileBuffer *fntbuf;
        if (!find(TAG_FNT, fntbuf))
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        m_font = new Font;
        fntbuf->skip(2);
        m_font->setHeight((unsigned int)fntbuf->getUint8());
        fntbuf->skip(1);
        m_font->setFirst((unsigned int)fntbuf->getUint8());
        unsigned int numChars = (unsigned int)fntbuf->getUint8();
        fntbuf->skip(2);
        if (fntbuf->getUint8() != 0x01)
        {
            clearTags();
            throw CompressionError(__FILE__, __LINE__);
        }
        unsigned int size = (unsigned int)fntbuf->getUint32LE();
        FileBuffer *glyphbuf = new FileBuffer(size);
        fntbuf->decompressRLE(glyphbuf);
        unsigned int *glyphOffset = new unsigned int [numChars];
        for (unsigned int i = 0; i < numChars; i++)
        {
            glyphOffset[i] = glyphbuf->getUint16LE();
        }
        unsigned int glyphDataStart = glyphbuf->getBytesDone();
        for (unsigned int i = 0; i < numChars; i++)
        {
            FontGlyph glyph;
            glyphbuf->seek(glyphDataStart + i);
            glyph.width = (unsigned int)glyphbuf->getUint8();
            glyphbuf->seek(glyphDataStart + numChars + glyphOffset[i]);
            for (int j = 0; j < m_font->getHeight(); j++)
            {
                glyph.data[j] = (uint16_t)glyphbuf->getUint8() << 8;
                if (glyph.width > 8)
                {
                    glyph.data[j] += (uint16_t)glyphbuf->getUint8();
                }
            }
            m_font->addGlyph(glyph);
        }
        delete[] glyphOffset;
        delete glyphbuf;
        clearTags();
    }
    catch (Exception &e)
    {
        e.print("FontResource::Load");
        clearTags();
        throw;
    }
}

unsigned int
FontResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("FontResource::save");
        throw;
    }
}
