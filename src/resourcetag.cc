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
#include "resourcetag.h"

ResourceTag::ResourceTag()
    : m_tagMap()
{}

ResourceTag::~ResourceTag()
{
    m_tagMap.clear();
}

void
ResourceTag::load(FileBuffer *buffer)
{
    try
    {
        unsigned int n = buffer->getUint16LE();
        for (unsigned int i = 0; i < n; i++)
        {
            unsigned int id = buffer->getUint16LE();
            std::string name = buffer->getString();
            m_tagMap.insert(std::pair<const unsigned int, std::string>(id, name));
        }
    }
    catch (Exception &e)
    {
        e.print("ResourceTag::Load");
    }
}

bool
ResourceTag::find(const unsigned int id, std::string &name)
{
    try
    {
        name = m_tagMap[id];
    }
    catch (...)
    {
        return false;
    }
    return true;
}

