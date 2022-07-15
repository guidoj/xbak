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

#include "skillswidget.h"

SkillsWidget::SkillsWidget(const Rectangle &r, PlayerCharacter *pc, Image *sw, Image *bl, Font *f)
    : Widget(r)
    , m_playerCharacter(pc)
    , m_font(f)
    , m_leftSword(0)
    , m_leftBlood(0)
    , m_rightSword(0)
    , m_rightBlood(0)
    , m_defense(0)
    , m_crossbowAccuracy(0)
    , m_meleeAccuracy(0)
    , m_castingAccuracy(0)
    , m_assessment(0)
    , m_armorcraft(0)
    , m_weaponcraft(0)
    , m_barding(0)
    , m_haggling(0)
    , m_lockpick(0)
    , m_scouting(0)
    , m_stealth(0)
{
    m_leftSword = new Image(sw);
    m_leftBlood = new Image(bl);
    m_rightSword = new Image(sw);
    m_rightBlood = new Image(bl);
    m_rightSword->horizontalFlip();
    m_rightBlood->horizontalFlip();
    m_defense = new SkillLevelWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos(), 132, 25), LEFT_SIDE, m_leftSword, m_leftBlood, f);
    m_crossbowAccuracy = new SkillLevelWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos() + 16, 132, 25), LEFT_SIDE, m_leftSword, m_leftBlood, f);
    m_meleeAccuracy = new SkillLevelWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos() + 32, 132, 25), LEFT_SIDE, m_leftSword, m_leftBlood, f);
    m_castingAccuracy = new SkillLevelWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos() + 48, 132, 25), LEFT_SIDE, m_leftSword, m_leftBlood, f);
    m_assessment = new SkillLevelWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos() + 64, 132, 25), LEFT_SIDE, m_leftSword, m_leftBlood, f);
    m_armorcraft = new SkillLevelWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos() + 80, 132, 25), LEFT_SIDE, m_leftSword, m_leftBlood, f);
    m_weaponcraft = new SkillLevelWidget(Rectangle(m_rect.getXPos() + 145, m_rect.getYPos(), 132, 25), RIGHT_SIDE, m_rightSword, m_rightBlood, f);
    m_barding = new SkillLevelWidget(Rectangle(m_rect.getXPos() + 145, m_rect.getYPos() + 16, 132, 25), RIGHT_SIDE, m_rightSword, m_rightBlood, f);
    m_haggling = new SkillLevelWidget(Rectangle(m_rect.getXPos() + 145, m_rect.getYPos() + 32, 132, 25), RIGHT_SIDE, m_rightSword, m_rightBlood, f);
    m_lockpick = new SkillLevelWidget(Rectangle(m_rect.getXPos() + 145, m_rect.getYPos() + 48, 132, 25), RIGHT_SIDE, m_rightSword, m_rightBlood, f);
    m_scouting = new SkillLevelWidget(Rectangle(m_rect.getXPos() + 145, m_rect.getYPos() + 64, 132, 25), RIGHT_SIDE, m_rightSword, m_rightBlood, f);
    m_stealth = new SkillLevelWidget(Rectangle(m_rect.getXPos() + 145, m_rect.getYPos() + 80, 132, 25), RIGHT_SIDE, m_rightSword, m_rightBlood, f);
    m_defense->setLevel("Defense", pc->getStatistics().get(STAT_DEFENSE, STAT_ACTUAL));
    m_crossbowAccuracy->setLevel("Accy: Crossbow", pc->getStatistics().get(STAT_CROSSBOW_ACCURACY, STAT_ACTUAL));
    m_meleeAccuracy->setLevel("Accy: Melee", pc->getStatistics().get(STAT_MELEE_ACCURACY, STAT_ACTUAL));
    m_castingAccuracy->setLevel("Accy: Casting", pc->getStatistics().get(STAT_CASTING_ACCURACY, STAT_ACTUAL));
    m_assessment->setLevel("Assessment", pc->getStatistics().get(STAT_ASSESSMENT, STAT_ACTUAL));
    m_armorcraft->setLevel("Armorcraft", pc->getStatistics().get(STAT_ARMORCRAFT, STAT_ACTUAL));
    m_weaponcraft->setLevel("Weaponcraft", pc->getStatistics().get(STAT_WEAPONCRAFT, STAT_ACTUAL));
    m_barding->setLevel("Barding", pc->getStatistics().get(STAT_BARDING, STAT_ACTUAL));
    m_haggling->setLevel("Haggling", pc->getStatistics().get(STAT_HAGGLING, STAT_ACTUAL));
    m_lockpick->setLevel("Lockpick", pc->getStatistics().get(STAT_LOCKPICK, STAT_ACTUAL));
    m_scouting->setLevel("Scouting", pc->getStatistics().get(STAT_SCOUTING, STAT_ACTUAL));
    m_stealth->setLevel("Stealth", pc->getStatistics().get(STAT_STEALTH, STAT_ACTUAL));
}

SkillsWidget::~SkillsWidget()
{
    delete m_defense;
    delete m_crossbowAccuracy;
    delete m_meleeAccuracy;
    delete m_castingAccuracy;
    delete m_assessment;
    delete m_armorcraft;
    delete m_weaponcraft;
    delete m_barding;
    delete m_haggling;
    delete m_lockpick;
    delete m_scouting;
    delete m_stealth;
    delete m_leftSword;
    delete m_leftBlood;
    delete m_rightSword;
    delete m_rightBlood;
}

void
SkillsWidget::draw()
{
    if (isVisible())
    {
        m_defense->draw();
        m_crossbowAccuracy->draw();
        m_meleeAccuracy->draw();
        m_castingAccuracy->draw();
        m_assessment->draw();
        m_armorcraft->draw();
        m_weaponcraft->draw();
        m_barding->draw();
        m_haggling->draw();
        m_lockpick->draw();
        m_scouting->draw();
        m_stealth->draw();
    }
}

void
SkillsWidget::drag(const int, const int)
{}

void
SkillsWidget::drop(const int, const int)
{}
