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

#ifndef SKILLS_WIDGET_H
#define SKILLS_WIDGET_H

#include "playercharacter.h"
#include "skilllevelwidget.h"

class SkillsWidget
    : public Widget
{
private:
    PlayerCharacter *m_playerCharacter;
    Font *m_font;
    Image *m_leftSword;
    Image *m_leftBlood;
    Image *m_rightSword;
    Image *m_rightBlood;
    SkillLevelWidget *m_defense;
    SkillLevelWidget *m_crossbowAccuracy;
    SkillLevelWidget *m_meleeAccuracy;
    SkillLevelWidget *m_castingAccuracy;
    SkillLevelWidget *m_assessment;
    SkillLevelWidget *m_armorcraft;
    SkillLevelWidget *m_weaponcraft;
    SkillLevelWidget *m_barding;
    SkillLevelWidget *m_haggling;
    SkillLevelWidget *m_lockpick;
    SkillLevelWidget *m_scouting;
    SkillLevelWidget *m_stealth;
public:
    SkillsWidget ( const Rectangle &r, PlayerCharacter *pc, Image *sw, Image *bl, Font *f );
    virtual ~SkillsWidget();
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
