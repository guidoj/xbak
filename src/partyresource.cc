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
#include "partyresource.h"

PartyResource::PartyResource()
    : m_data()
{}

PartyResource::~PartyResource()
{
    clear();
}

unsigned int
PartyResource::getSize() const
{
    return m_data.size();
}

PartyData *
PartyResource::getData(const unsigned int n)
{
    return m_data[n];
}

void
PartyResource::clear()
{
    for (unsigned int i = 0; i < m_data.size(); i++)
    {
        delete m_data[i];
    }
    m_data.clear();
}

void
PartyResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        unsigned int offset[PARTY_SIZE];
        for (unsigned int i = 0; i < PARTY_SIZE; i++)
        {
            offset[i] = buffer->getUint16LE();
            buffer->skip(93);
        }
        buffer->skip(2);
        unsigned int start = buffer->getBytesDone();
        for (unsigned int i = 0; i < PARTY_SIZE; i++)
        {
            buffer->seek(start + offset[i]);
            PartyData *pd = new PartyData;
            pd->name = buffer->getString();
            m_data.push_back(pd);
        }
    }
    catch (Exception &e)
    {
        e.print("PartyResource::Load");
        throw;
    }
}

unsigned int
PartyResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("PartyResource::Save");
        throw;
    }
}
