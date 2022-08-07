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
#include "soundresource.h"
#include "resourcetag.h"

const unsigned int MAX_NUM_SFX = 1000;

SoundData::SoundData()
    : name()
    , type(SND_TYPE_UNKNOWN)
    , sounds()
{
}

SoundData::~SoundData()
{
    sounds.clear();
}

SoundResource* SoundResource::m_instance = 0;

SoundResource::SoundResource()
    : TaggedResource()
    , m_soundMap()
{
}

SoundResource::~SoundResource()
{
    clear();
}

SoundResource* SoundResource::getInstance()
{
    if (m_instance == 0)
    {
        m_instance = new SoundResource();
        FileManager::getInstance()->load(m_instance, "frp.sx");
    }
    return m_instance;
}

void SoundResource::cleanUp()
{
    if (m_instance != 0)
    {
        delete m_instance;
        m_instance = 0;
    }
}

SoundData& SoundResource::getSoundData(unsigned int id)
{
    return m_soundMap[id];
}

void SoundResource::clear()
{
    for (std::map<unsigned int, SoundData>::iterator it = m_soundMap.begin(); it != m_soundMap.end(); ++it)
    {
        SoundData data = it->second;
        for (std::vector<Sound *>::iterator it2 = data.sounds.begin(); it2 != data.sounds.end(); ++it2)
        {
            delete (*it2);
        }
    }
    m_soundMap.clear();
}

void SoundResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        split(buffer);
        FileBuffer *infbuf;
        FileBuffer *tagbuf;
        if (!find(TAG_INF, infbuf) ||
                !find(TAG_TAG, tagbuf))
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        infbuf->skip(2);
        unsigned int n = infbuf->getUint16LE();
        infbuf->skip(1);
        ResourceTag tags;
        tags.load(tagbuf);
        for (unsigned int i = 0; i < n; i++)
        {
            unsigned int id = infbuf->getUint16LE();
            std::streamoff offset = infbuf->getUint32LE();
            std::string name;
            if (tags.find(id, name))
            {
                buffer->seek(offset + 8);
                if (id != buffer->getUint16LE())
                {
                    clearTags();
                    throw DataCorruption(__FILE__, __LINE__);
                }
                SoundData data;
                data.name = name;
                data.type = (SoundType)buffer->getUint8();
                buffer->skip(2);
                FileBuffer *sndbuf = new FileBuffer(buffer->getUint32LE() - 2);
                buffer->skip(2);
                sndbuf->fill(buffer);
                buffer->skip(-sndbuf->getSize());
                int code = buffer->getUint8();
                while (code != 0xff)
                {
                    Sound *sound = new Sound(code);
                    std::vector<unsigned int> offsetVec;
                    std::vector<unsigned int> sizeVec;
                    code = buffer->getUint8();
                    while (code != 0xff)
                    {
                        buffer->skip(1);
                        offsetVec.push_back(buffer->getUint16LE());
                        sizeVec.push_back(buffer->getUint16LE());
                        code = buffer->getUint8();
                    }
                    for (unsigned int j = 0; j < offsetVec.size(); j++)
                    {
                        sndbuf->seek(offsetVec[j]);
                        FileBuffer *samplebuf = new FileBuffer(sizeVec[j]);
                        samplebuf->fill(sndbuf);
                        sound->addVoice(samplebuf);
                        delete samplebuf;
                    }
                    sound->generateBuffer();
                    data.sounds.push_back(sound);
                    code = buffer->getUint8();
                }
                m_soundMap.insert(std::pair<unsigned int, SoundData>(id, data));
                delete sndbuf;
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
        e.print("SoundResource::Load");
        clearTags();
        throw;
    }
}

unsigned int SoundResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("SoundResource::Save");
        throw;
    }
}
