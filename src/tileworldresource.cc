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
#include "tileworldresource.h"

TileWorldResource::TileWorldResource()
    : m_xCenter(0)
    , m_yCenter(0)
    , m_items()
{}

TileWorldResource::~TileWorldResource()
{
    clear();
}

unsigned int
TileWorldResource::getMinX() const
{
    return m_xCenter - TILE_SIZE_2;
}

unsigned int
TileWorldResource::getMaxX() const
{
    return m_xCenter + TILE_SIZE_2;
}

unsigned int
TileWorldResource::getMinY() const
{
    return m_yCenter - TILE_SIZE_2;
}

unsigned int
TileWorldResource::getMaxY() const
{
    return m_yCenter + TILE_SIZE_2;
}

unsigned int
TileWorldResource::getSize() const
{
    return m_items.size();
}

TileWorldItem&
TileWorldResource::getItem(unsigned int i)
{
    return m_items[i];
}

void
TileWorldResource::clear()
{
    m_items.clear();
}

void
TileWorldResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        while (!buffer->atEnd())
        {
            TileWorldItem twi;
            twi.type = buffer->getUint32LE();
            twi.flags = buffer->getUint32LE();
            twi.xloc = buffer->getUint32LE();
            twi.yloc = buffer->getUint32LE();
            if (twi.type == OBJECT_CENTER)
            {
                m_xCenter = twi.xloc;
                m_yCenter = twi.yloc;
            }
            m_items.push_back(twi);
            buffer->skip(4);
        }
    }
    catch (Exception &e)
    {
        e.print("TileWorldResource::Load");
        throw;
    }
}

unsigned int
TileWorldResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("TileWorldResource::Save");
        throw;
    }
}
