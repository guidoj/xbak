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
#include "labelresource.h"

LabelResource::LabelResource()
    : m_data()
{}

LabelResource::~LabelResource()
{
    clear();
}

unsigned int
LabelResource::getSize() const
{
    return m_data.size();
}

LabelData&
LabelResource::getLabelData(const unsigned int n)
{
    return m_data[n];
}

void
LabelResource::clear()
{
    m_data.clear();
}

void
LabelResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        unsigned int numRecords = buffer->getUint16LE();
        int *offset = new int[numRecords];
        for (unsigned int i = 0; i < numRecords; i++)
        {
            LabelData lblData;
            offset[i] = buffer->getSint16LE();
            lblData.xpos = buffer->getSint16LE();
            lblData.ypos = buffer->getSint16LE();
            lblData.type = buffer->getSint16LE();
            lblData.color = buffer->getSint8();
            lblData.shadow = buffer->getSint8();
            m_data.push_back(lblData);
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
        e.print("LabelResource::Load");
        throw;
    }
}

unsigned int
LabelResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("LabelResource::Save");
        throw;
    }
}
