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

#include "preferences.h"

Preferences::Preferences()
{
    setDefaults();
}

Preferences::~Preferences()
{}

void
Preferences::setDefaults()
{
    m_stepSize = STS_SMALL;
    m_turnSize = STS_SMALL;
    m_textSpeed = TS_WAIT;
    m_detail = LOD_MAX;
    m_sound = true;
    m_music = true;
    m_combatMusic = true;
    m_cdMusic = false;
    m_introduction = true;
}

void
Preferences::copy(const Preferences &prefs)
{
    m_stepSize = prefs.m_stepSize;
    m_turnSize = prefs.m_turnSize;
    m_textSpeed = prefs.m_textSpeed;
    m_detail = prefs.m_detail;
    m_sound = prefs.m_sound;
    m_music = prefs.m_music;
    m_combatMusic = prefs.m_combatMusic;
    m_introduction = prefs.m_introduction;
}

StepTurnSize
Preferences::getStepSize() const
{
    return m_stepSize;
}

void
Preferences::setStepSize(const StepTurnSize sz)
{
    m_stepSize = sz;
}

StepTurnSize
Preferences::getTurnSize() const
{
    return m_turnSize;
}

void
Preferences::setTurnSize(const StepTurnSize sz)
{
    m_turnSize = sz;
}

TextSpeed
Preferences::getTextSpeed() const
{
    return m_textSpeed;
}

void
Preferences::setTextSpeed(const TextSpeed ts)
{
    m_textSpeed = ts;
}

LevelOfDetail
Preferences::getDetail() const
{
    return m_detail;
}

void
Preferences::setDetail(const LevelOfDetail lod)
{
    m_detail = lod;
}

bool
Preferences::getSound() const
{
    return m_sound;
}

void
Preferences::setSound(const bool toggle)
{
    m_sound = toggle;
}

bool
Preferences::getMusic() const
{
    return m_music;
}

void
Preferences::setMusic(const bool toggle)
{
    m_music = toggle;
}

bool
Preferences::getCombatMusic() const
{
    return m_combatMusic;
}

void
Preferences::setCombatMusic(const bool toggle)
{
    m_combatMusic = toggle;
}

bool
Preferences::getCdMusic() const
{
    return m_cdMusic;
}

void
Preferences::setCdMusic(const bool toggle)
{
    m_cdMusic = toggle;
}

bool
Preferences::getIntroduction() const
{
    return m_introduction;
}

void
Preferences::setIntroduction(const bool toggle)
{
    m_introduction = toggle;
}
