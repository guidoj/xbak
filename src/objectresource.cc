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
#include "filemanager.h"
#include "objectresource.h"

ObjectResource* ObjectResource::m_instance = 0;

ObjectResource::ObjectResource()
    : m_data()
{}

ObjectResource::~ObjectResource()
{
    clear();
}

ObjectResource*
ObjectResource::getInstance()
{
    if (!m_instance)
    {
        m_instance = new ObjectResource();
        FileManager::getInstance()->load(m_instance, "OBJINFO.DAT");
    }
    return m_instance;
}

void ObjectResource::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

unsigned int
ObjectResource::getSize() const
{
    return m_data.size();
}

ObjectInfo&
ObjectResource::getObjectInfo(unsigned int n)
{
    return m_data[n];
}

void
ObjectResource::clear()
{
    m_data.clear();
}

void
ObjectResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        for (unsigned int i = 0; i < 138; i++)
        {
            ObjectInfo obj;
            obj.name = buffer->getString(30);
            buffer->skip(2);
            obj.flags = buffer->getUint16LE();
            buffer->skip(2);
            obj.level = buffer->getSint16LE();
            obj.value = buffer->getSint16LE();
            obj.strengthSwing = buffer->getSint16LE();
            obj.strengthThrust = buffer->getSint16LE();
            obj.accuracySwing = buffer->getSint16LE();
            obj.accuracyThrust = buffer->getSint16LE();
            buffer->skip(2);
            obj.imageSize = buffer->getUint16LE();
            buffer->skip(4);
            obj.race = (Race)(buffer->getUint16LE());
            buffer->skip(2);
            obj.type = (ObjectType)(buffer->getUint16LE());
            obj.effectMask = buffer->getUint16LE();
            obj.effect = buffer->getSint16LE();
            buffer->skip(4);
            obj.modifierMask = buffer->getUint16LE();
            obj.modifier = buffer->getSint16LE();
            buffer->skip(6);
            m_data.push_back(obj);
        }
    }
    catch (Exception &e)
    {
        e.print("ObjectResource::Load");
        throw;
    }
}

unsigned int
ObjectResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("ObjectResource::Save");
        throw;
    }
}
