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
#include "nameresource.h"

NameResource::NameResource()
    : m_name()
{}

NameResource::~NameResource()
{
    clear();
}

unsigned int
NameResource::getSize() const
{
    return m_name.size();
}

std::string
NameResource::getName(unsigned int n) const
{
    return m_name[n];
}

void
NameResource::clear()
{
    m_name.clear();
}

void
NameResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        unsigned int n = buffer->getUint16LE();
        unsigned int *offset = new unsigned int[n];
        for (unsigned int i = 0; i < n; i++)
        {
            offset[i] = buffer->getUint16LE();
        }
        buffer->skip(2);
        unsigned int start = buffer->getBytesDone();
        for (unsigned int i = 0; i < n; i++)
        {
            buffer->seek(start + offset[i]);
            m_name.push_back(buffer->getString());
        }
        delete[] offset;
    }
    catch (Exception &e)
    {
        e.print("NameResource::Load");
        throw;
    }
}

unsigned int
NameResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("NameResource::Save");
        throw;
    }
}
