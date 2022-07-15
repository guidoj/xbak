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
#include "playercharacter.h"

PlayerCharacter::PlayerCharacter(const std::string& s)
    : m_name(s)
    , m_statistics()
    , m_buttonImage(0)
    , m_portraitImage(0)
    , m_order(-1)
    , m_selected(false)
{
    m_charClass = CLASS_WARRIOR;
    m_condition = COND_NORMAL;
    m_inventory = new Inventory;
}

PlayerCharacter::~PlayerCharacter()
{
    delete m_inventory;
}

std::string&
PlayerCharacter::getName()
{
    return m_name;
}

void
PlayerCharacter::setName(const std::string& s)
{
    m_name = s;
}

Statistics&
PlayerCharacter::getStatistics()
{
    return m_statistics;
}

Image *
PlayerCharacter::getButtonImage() const
{
    return m_buttonImage;
}

void
PlayerCharacter::setButtonImage(Image *img)
{
    if (!img)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_buttonImage = img;
}

Image *
PlayerCharacter::getPortraitImage() const
{
    return m_portraitImage;
}

void
PlayerCharacter::setPortraitImage(Image *img)
{
    if (!img)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_portraitImage = img;
}

CharacterClass
PlayerCharacter::getCharacterClass() const
{
    return m_charClass;
}

void
PlayerCharacter::setCharacterClass(const CharacterClass cc)
{
    m_charClass = cc;
}

ConditionType
PlayerCharacter::setCondition() const
{
    return m_condition;
}

void
PlayerCharacter::setCondition(const ConditionType ct)
{
    m_condition = ct;
    notify();
}

Inventory *
PlayerCharacter::getInventory() const
{
    return m_inventory;
}

int
PlayerCharacter::getOrder() const
{
    return m_order;
}

void
PlayerCharacter::setOrder(const int n)
{
    m_order = n;
}

bool
PlayerCharacter::isSelected() const
{
    return m_selected;
}

void
PlayerCharacter::select(const bool toggle)
{
    m_selected = toggle;
    notify();
}
