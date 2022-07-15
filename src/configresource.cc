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
#include "configresource.h"

ConfigResource::ConfigResource()
    : m_prefs(0)
{
}

ConfigResource::~ConfigResource()
{
    if (m_prefs)
    {
        delete m_prefs;
    }
}

Preferences * ConfigResource::getPreferences()
{
    return m_prefs;
}

void ConfigResource::setPreferences(Preferences *p)
{
    m_prefs = p;
}

const unsigned int PREF_SOUND_MASK        = 0x01;
const unsigned int PREF_MUSIC_MASK        = 0x02;
const unsigned int PREF_COMBATMUSIC_MASK  = 0x04;
const unsigned int PREF_INTRODUCTION_MASK = 0x08;
const unsigned int PREF_CD_MUSIC_MASK     = 0x10;

void ConfigResource::load(FileBuffer *buffer)
{
    if (!m_prefs)
    {
        m_prefs = new Preferences();
    }
    try
    {
        m_prefs->setStepSize((StepTurnSize)buffer->getUint8());
        m_prefs->setTurnSize((StepTurnSize)buffer->getUint8());
        m_prefs->setDetail((LevelOfDetail)buffer->getUint8());
        m_prefs->setTextSpeed((TextSpeed)buffer->getUint8());
        unsigned int flags = (unsigned int)buffer->getUint8();
        m_prefs->setSound(flags & PREF_SOUND_MASK);
        m_prefs->setMusic(flags & PREF_MUSIC_MASK);
        m_prefs->setCombatMusic(flags & PREF_COMBATMUSIC_MASK);
        m_prefs->setIntroduction(flags & PREF_INTRODUCTION_MASK);
        m_prefs->setCdMusic(flags & PREF_CD_MUSIC_MASK);
    }
    catch (Exception &e)
    {
        e.print("ConfigResource::Load");
        throw;
    }
}

unsigned int ConfigResource::save(FileBuffer *buffer)
{
    if (!m_prefs)
    {
        throw NullPointer(__FILE__, __LINE__, "prefs");
    }
    try
    {
        buffer->rewind();
        buffer->putUint8((unsigned int)m_prefs->getStepSize());
        buffer->putUint8((unsigned int)m_prefs->getTurnSize());
        buffer->putUint8((unsigned int)m_prefs->getDetail());
        buffer->putUint8((unsigned int)m_prefs->getTextSpeed());
        unsigned int flags = 0;
        if (m_prefs->getSound()) flags |= PREF_SOUND_MASK;
        if (m_prefs->getMusic()) flags |= PREF_MUSIC_MASK;
        if (m_prefs->getCombatMusic()) flags |= PREF_COMBATMUSIC_MASK;
        if (m_prefs->getIntroduction()) flags |= PREF_INTRODUCTION_MASK;
        buffer->putUint8(flags);
        return buffer->getBytesDone();
    }
    catch (Exception &e)
    {
        e.print("ConfigResource::Save");
        throw;
    }
}
