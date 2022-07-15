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

#ifndef ANIMATION_RESOURCE_H
#define ANIMATION_RESOURCE_H

#include "taggedresource.h"

struct AnimationData
{
    std::string m_name;
    std::string m_resource;
};

class AnimationResource: public TaggedResource
{
private:
    std::string m_version;
    std::map<unsigned int, AnimationData> m_animationMap;
    FileBuffer *m_script;
public:
    AnimationResource();
    virtual ~AnimationResource();
    std::string &getVersion();
    FileBuffer * getScript() const;
    AnimationData &getAnimationData ( unsigned int id );
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif

