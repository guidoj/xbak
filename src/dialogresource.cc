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
#include "dialogresource.h"

DialogData::DialogData()
    : m_childDialogs(0)
    , m_text()
    , m_childData()
{
}

DialogData::~DialogData()
{
    m_text.clear();
    for (unsigned int i = 0; i < m_childData.size(); i++)
    {
        delete m_childData[i];
    }
    m_childData.clear();
}

DialogResource::DialogResource()
    : m_dialogMap()
{
}

DialogResource::~DialogResource()
{
    clear();
}

unsigned int DialogResource::getSize() const
{
    return m_dialogMap.size();
}

bool DialogResource::find(const unsigned int n, DialogData* &data)
{
    std::map<const unsigned int, DialogData*>::iterator it = m_dialogMap.find(n);
    if (it != m_dialogMap.end())
    {
        data = it->second;
        return true;
    }
    return false;
}

void DialogResource::clear()
{
    for (std::map<const unsigned int, DialogData*>::iterator it = m_dialogMap.begin(); it != m_dialogMap.end(); ++it)
    {
        delete it->second;
    }
    m_dialogMap.clear();
}

typedef struct _DialogPageOffset
{
    int type;
    unsigned int offset;
}
DialogPageOffset;

void DialogResource::readDialogData(FileBuffer *buffer, DialogData *data)
{
    try
    {
        buffer->skip(5);
        data->m_childDialogs = buffer->getUint8();
        unsigned int n = buffer->getUint8();
        unsigned int length = buffer->getUint16LE();
        std::vector<DialogPageOffset> pageOffset;
        for (unsigned int i = 0; i < data->m_childDialogs; i++)
        {
            DialogPageOffset dpo;
            buffer->skip(4);
            dpo.type = buffer->getSint16LE();
            dpo.offset = buffer->getUint32LE();
            pageOffset.push_back(dpo);
        }
        for (unsigned int i = 0; i < data->m_childDialogs; i++)
        {
            if (pageOffset[i].type != 0)
            {
                buffer->seek(pageOffset[i].offset & 0x7fffffff);
                DialogData* child = new DialogData;
                readDialogData(buffer, child);
                data->m_childData.push_back(child);
            }
        }
        for (unsigned int j = 0; j < n; j++)
        {
            buffer->skip(10);
        }
        std::string s = buffer->getString(length);
        data->m_text.push_back(s);
        pageOffset.clear();
    }
    catch (Exception &e)
    {
        e.print("DialogResource::ReadDialogData");
        throw;
    }
}

void DialogResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        unsigned int n = buffer->getUint16LE();
        std::map<const unsigned int, unsigned int> offset;
        for (unsigned int i = 0; i < n; i++)
        {
            unsigned int key = buffer->getUint32LE();
            unsigned int value = buffer->getUint32LE();
            offset.insert(std::pair<const unsigned int, unsigned int>(key, value));
        }
        for (std::map<const unsigned int, unsigned int>::const_iterator it = offset.begin(); it != offset.end(); ++it)
        {
            buffer->seek(it->second);
            DialogData* data = new DialogData;
            readDialogData(buffer, data);
            m_dialogMap.insert(std::pair<const unsigned int, DialogData*>(it->first, data));
        }
        offset.clear();
    }
    catch (Exception &e)
    {
        e.print("DialogResource::Load");
        throw;
    }
}

unsigned int DialogResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("DialogResource::Save");
        throw;
    }
}
