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

#include "animationresource.h"
#include "exception.h"
#include "resourcetag.h"

AnimationResource::AnimationResource()
    : TaggedResource()
    , m_version()
    , m_animationMap()
    , m_script(0)
{}

AnimationResource::~AnimationResource()
{
    clear();
}

std::string&
AnimationResource::getVersion()
{
    return m_version;
}

FileBuffer *
AnimationResource::getScript() const
{
    return m_script;
}

AnimationData&
AnimationResource::getAnimationData(unsigned int id)
{
    return m_animationMap[id];
}

void
AnimationResource::clear()
{
    m_animationMap.clear();
    if (m_script)
    {
        delete m_script;
        m_script = 0;
    }
}

void
AnimationResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        split(buffer);
        FileBuffer *verbuf;
        FileBuffer *resbuf;
        FileBuffer *scrbuf;
        FileBuffer *tagbuf;
        if (!find(TAG_VER, verbuf) ||
                !find(TAG_RES, resbuf) ||
                !find(TAG_SCR, scrbuf) ||
                !find(TAG_TAG, tagbuf))
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        m_version = verbuf->getString();
        if (scrbuf->getUint8() != 0x02)
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        m_script = new FileBuffer(scrbuf->getUint32LE());
        scrbuf->decompressLZW(m_script);
        ResourceTag tags;
        tags.load(tagbuf);
        unsigned int n = resbuf->getUint16LE();
        for (unsigned int i = 0; i < n; i++)
        {
            unsigned int id = resbuf->getUint16LE();
            std::string resource = resbuf->getString();
            std::string name;
            if (tags.find(id, name))
            {
                AnimationData data;
                data.m_name = name;
                data.m_resource = resource;
                m_animationMap.insert(std::pair<unsigned int, AnimationData>(id, data));
            }
            else
            {
                throw DataCorruption(__FILE__, __LINE__);
            }
        }
        clearTags();
    }
    catch (Exception &e)
    {
        e.print("AnimationResource::load");
        clearTags();
        throw;
    }
}

unsigned int
AnimationResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("AnimationResource::save");
        throw;
    }
}
