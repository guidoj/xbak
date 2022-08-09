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

#ifndef OBJECT_RESOURCE_H
#define OBJECT_RESOURCE_H

#include <vector>

#include "resourcedata.h"

typedef enum _Race
{
    RC_NONE,
    RC_TSURANI,
    RC_ELF,
    RC_HUMAN,
    RC_DWARF
} Race;

typedef enum _ObjectType
{
    OT_UNSPECIFIED,
    OT_SWORD,
    OT_CROSSBOW,
    OT_STAFF,
    OT_ARMOR,
    OT_UNKNOWN5,
    OT_UNKNOWN6,
    OT_KEY,
    OT_TOOL,
    OT_WEAPON_OIL,
    OT_ARMOR_OIL,
    OT_SPECIAL_OIL,
    OT_BOWSTRING,
    OT_SCROLL,
    OT_UNKNOWN14,
    OT_UNKNOWN15,
    OT_NOTE,
    OT_BOOK,
    OT_POTION,
    OT_RESTORATIVES,
    OT_CONTAINER,
    OT_LIGHTER,
    OT_INGREDIENT,
    OT_RATION,
    OT_FOOD,
    OT_OTHER
} ObjectType;

struct ObjectInfo
{
    std::string name;
    unsigned int flags;
    int level;
    int value;
    int strengthSwing;
    int accuracySwing;
    int strengthThrust;
    int accuracyThrust;
    unsigned int imageSize;
    Race race;
    ObjectType type;
    unsigned int effectMask;
    int effect;
    unsigned int modifierMask;
    int modifier;
};

class ObjectResource
    : public ResourceData
{
private:
    std::vector<ObjectInfo> m_data;
    static ObjectResource *m_instance;

protected:
    ObjectResource();

public:
    virtual ~ObjectResource();
    static ObjectResource* getInstance();
    static void cleanUp();
    unsigned int getSize() const;
    ObjectInfo& getObjectInfo ( unsigned int n );
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif
