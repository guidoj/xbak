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
#include "requestresource.h"

RequestResource::RequestResource()
    : m_popup(false)
    , m_rect(0, 0, 0, 0)
    , m_xoff(0)
    , m_yoff(0)
    , m_data()
{}

RequestResource::~RequestResource()
{
    clear();
}

bool
RequestResource::isPopup() const
{
    return m_popup;
}

Rectangle &
RequestResource::getRectangle()
{
    return m_rect;
}

int
RequestResource::getXOff() const
{
    return m_xoff;
}

int
RequestResource::getYOff() const
{
    return m_yoff;
}

unsigned int
RequestResource::getSize() const
{
    return m_data.size();
}

RequestData
RequestResource::getRequestData(const unsigned int n) const
{
    return m_data[n];
}

void
RequestResource::clear()
{
    m_data.clear();
}

void
RequestResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        buffer->skip(2);
        m_popup = (buffer->getSint16LE() != 0);
        buffer->skip(2);
        m_rect.setXPos(buffer->getSint16LE());
        m_rect.setYPos(buffer->getSint16LE());
        m_rect.setWidth(buffer->getSint16LE());
        m_rect.setHeight(buffer->getSint16LE());
        buffer->skip(2);
        m_xoff = buffer->getSint16LE();
        m_yoff = buffer->getSint16LE();
        buffer->skip(2);
        buffer->skip(2);
        buffer->skip(2);
        buffer->skip(2);
        unsigned int numRecords = buffer->getUint16LE();
        int *offset = new int[numRecords];
        for (unsigned int i = 0; i < numRecords; i++)
        {
            RequestData reqData;
            reqData.widget = buffer->getUint16LE();
            reqData.action = buffer->getSint16LE();
            reqData.visible = (buffer->getUint8() > 0);
            buffer->skip(2);
            buffer->skip(2);
            buffer->skip(2);
            reqData.xpos = buffer->getSint16LE();
            reqData.ypos = buffer->getSint16LE();
            reqData.width = buffer->getUint16LE();
            reqData.height = buffer->getUint16LE();
            buffer->skip(2);
            offset[i] = buffer->getSint16LE();
            reqData.teleport = buffer->getSint16LE();
            reqData.image = buffer->getUint16LE();
            reqData.image = (reqData.image >> 1) + (reqData.image & 1);
            buffer->skip(2);
            reqData.group = buffer->getUint16LE();
            buffer->skip(2);
            m_data.push_back(reqData);
        }
        buffer->skip(2);
        unsigned int start = buffer->getBytesDone();
        for (unsigned int i = 0; i < numRecords; i++)
        {
            if (offset[i] >= 0)
            {
                buffer->seek(start + offset[i]);
                m_data[i].label = buffer->getString();
            }
        }
        delete[] offset;
    }
    catch (Exception &e)
    {
        e.print("RequestResource::Load");
        throw;
    }
}

unsigned int
RequestResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("RequestResource::Save");
        throw;
    }
}
