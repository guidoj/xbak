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
#include "rampresource.h"

RampResource::RampResource()
    : m_ramp()
{
}

RampResource::~RampResource()
{
    clear();
}

unsigned int RampResource::getSize() const
{
    return m_ramp.size();
}

std::vector<unsigned char>& RampResource::getRamp(unsigned int rmp)
{
    return m_ramp[rmp];
}

unsigned char RampResource::getColor(unsigned int rmp, unsigned int n) const
{
    return m_ramp[rmp][n];
}

void RampResource::clear()
{
    m_ramp.clear();
}

void RampResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        while (buffer->getBytesLeft() > 0)
        {
            std::vector<unsigned char> colors(256);
            for (unsigned int i = 0; i < 256; i++)
            {
                colors[i] = buffer->getUint8();
            }
            m_ramp.push_back(colors);
        }
    }
    catch (Exception &e)
    {
        e.print("RampResource::Load");
        throw;
    }
}

unsigned int RampResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("RampResource::Save");
        throw;
    }
}
