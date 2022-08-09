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

#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "image.h"
#include "inventory.h"
#include "statistics.h"

typedef enum _CharacterClass
{
    CLASS_WARRIOR,
    CLASS_SPELLCASTER
} CharacterClass;

typedef enum _ConditionType
{
    COND_NORMAL,
    COND_SICK,
    COND_PLAGUED,
    COND_POISONED,
    COND_DRUNK,
    COND_HEALING,
    COND_STARVING,
    COND_NEAR_DEATH
} ConditionType;

class PlayerCharacter
    : public Subject
{
private:
    std::string m_name;
    Statistics m_statistics;
    Image *m_buttonImage;
    Image *m_portraitImage;
    int m_order;
    bool m_selected;
    CharacterClass m_charClass;
    ConditionType m_condition;
    Inventory *m_inventory;

public:
    PlayerCharacter ( const std::string& s );
    virtual ~PlayerCharacter();
    std::string& getName();
    void setName ( const std::string& s );
    Statistics& getStatistics();
    Image* getButtonImage() const;
    void setButtonImage ( Image *img );
    Image* getPortraitImage() const;
    void setPortraitImage ( Image *img );
    int getOrder() const;
    void setOrder ( const int n );
    bool isSelected() const;
    void select ( const bool toggle );
    CharacterClass getCharacterClass() const;
    void setCharacterClass ( const CharacterClass cc );
    ConditionType setCondition() const;
    void setCondition ( const ConditionType ct );
    Inventory* getInventory() const;
};

#endif

