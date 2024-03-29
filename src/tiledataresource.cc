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
#include "tiledataresource.h"

TileDataResource::TileDataResource()
{}

TileDataResource::~TileDataResource()
{
    clear();
}

void
TileDataResource::clear()
{}

void
TileDataResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        for (unsigned int n = 0; n < 10; ++n)
        {
            buffer->seek(192 * n);
            unsigned int numTileDataBlocks = buffer->getUint16LE();
            while (numTileDataBlocks > 0)
            {
                // TODO
                buffer->getUint16LE();
                buffer->getUint16LE();
                buffer->getUint16LE();
                buffer->getUint8();
                buffer->getUint16LE();
                buffer->getUint16LE();
                buffer->getUint16LE();
                buffer->getUint16LE();
                buffer->getUint16LE();
                buffer->getUint16LE();
                --numTileDataBlocks;
            }
        }
    }
    catch (Exception &e)
    {
        e.print("TileDataResource::load");
        throw;
    }
}

unsigned int
TileDataResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("TileDataResource::save");
        throw;
    }
}
