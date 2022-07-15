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
#include "taggedresource.h"

TaggedResource::TaggedResource()
    : m_bufferMap()
{}

TaggedResource::~TaggedResource()
{
    clearTags();
}

void
TaggedResource::clearTags()
{
    for (std::map<const unsigned int, FileBuffer*>::iterator it = m_bufferMap.begin(); it != m_bufferMap.end(); ++it)
    {
        delete it->second;
    }
    m_bufferMap.clear();
}

void
TaggedResource::split(FileBuffer *buffer)
{
    while (!buffer->atEnd())
    {
        unsigned int label = buffer->getUint32LE();
        switch (label)
        {
        case TAG_ADS:
        case TAG_APP:
        case TAG_BIN:
        case TAG_BMP:
        case TAG_DAT:
        case TAG_FNT:
        case TAG_GID:
        case TAG_INF:
        case TAG_MAP:
        case TAG_PAG:
        case TAG_PAL:
        case TAG_RES:
        case TAG_SCR:
        case TAG_SND:
        case TAG_TAG:
        case TAG_TT3:
        case TAG_TTI:
        case TAG_VER:
        case TAG_VGA:
        {
            unsigned int size = buffer->getUint32LE();
            std::map<const unsigned int, FileBuffer*>::iterator it = m_bufferMap.find(label);
            if (it != m_bufferMap.end())
            {
                delete it->second;
                m_bufferMap.erase(it);
            }
            if (size & 0x80000000)
            {
                FileBuffer *lblbuf = new FileBuffer(size & 0x7fffffff);
                lblbuf->fill(buffer);
                m_bufferMap.insert(std::pair<const unsigned int, FileBuffer*>(label, 0));
                split(lblbuf);
                delete lblbuf;
            }
            else
            {
                FileBuffer *lblbuf = new FileBuffer(size);
                lblbuf->fill(buffer);
                m_bufferMap.insert(std::pair<const unsigned int, FileBuffer*>(label, lblbuf));
            }
        }
        break;
        default:
            throw UnexpectedValue(__FILE__, __LINE__, label);
            break;
        }
    }
}

bool
TaggedResource::find(const unsigned int label, FileBuffer* &buffer)
{
    try
    {
        buffer = m_bufferMap[label];
    }
    catch (...)
    {
        return false;
    }
    return (buffer != 0);
}
