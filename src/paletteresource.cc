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
#include "paletteresource.h"

PaletteResource::PaletteResource()
    : TaggedResource()
{
    m_palette = new Palette(0);
}

PaletteResource::~PaletteResource()
{
    clear();
}

Palette *
PaletteResource::getPalette() const
{
    return m_palette;
}

void
PaletteResource::clear()
{
    if (m_palette)
    {
        delete m_palette;
        m_palette = 0;
    }
}

void
PaletteResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        split(buffer);
        FileBuffer *vgabuf;
        if (!find(TAG_VGA, vgabuf))
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        unsigned int size = vgabuf->getSize() / 3;
        m_palette = new Palette(size);
        for (unsigned int i = 0; i < size; i++)
        {
            Color c;
            c.r = (vgabuf->getUint8() << 2);
            c.g = (vgabuf->getUint8() << 2);
            c.b = (vgabuf->getUint8() << 2);
            c.a = 0;
            m_palette->setColor(i, c);
        }
        clearTags();
    }
    catch (Exception &e)
    {
        e.print("PaletteResource::Load");
        clearTags();
        throw;
    }
}

unsigned int
PaletteResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("PaletteResource::Save");
        throw;
    }
}
