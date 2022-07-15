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

#ifndef SOUND_RESOURCE_H
#define SOUND_RESOURCE_H

#include <vector>

#include "sound.h"
#include "taggedresource.h"

class SoundData
{
public:
    SoundData();
    ~SoundData();
    std::string name;
    unsigned int type;
    std::vector<Sound *> sounds;
};

class SoundResource
    : public TaggedResource
{
private:
    std::map<unsigned int, SoundData> m_soundMap;
    static SoundResource* m_instance;
protected:
    SoundResource();
public:
    ~SoundResource();
    static SoundResource* getInstance();
    static void cleanUp();
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
    SoundData& getSoundData ( unsigned int id );
};

#endif
