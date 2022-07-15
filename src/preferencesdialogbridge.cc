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
#include "gameapplication.h"
#include "preferencesdialogbridge.h"
#include "requestresource.h"

PreferencesDialogBridge* PreferencesDialogBridge::m_instance = 0;

PreferencesDialogBridge::PreferencesDialogBridge()
{}

PreferencesDialogBridge::~PreferencesDialogBridge()
{}

PreferencesDialogBridge*
PreferencesDialogBridge::getInstance()
{
    if (!m_instance)
    {
        m_instance = new PreferencesDialogBridge();
    }
    return m_instance;
}


void
PreferencesDialogBridge::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
PreferencesDialogBridge::fetch()
{
    m_prefs.copy(*(GameApplication::getInstance()->getPreferences()));
}

void
PreferencesDialogBridge::commit()
{
    GameApplication::getInstance()->getPreferences()->copy(m_prefs);
}

bool
PreferencesDialogBridge::getSelectState(const unsigned int action)
{
    switch (action)
    {
    case PREF_STEP_SMALL:
        return m_prefs.getStepSize() == STS_SMALL;
        break;
    case PREF_STEP_MEDIUM:
        return m_prefs.getStepSize() == STS_MEDIUM;
        break;
    case PREF_STEP_LARGE:
        return m_prefs.getStepSize() == STS_LARGE;
        break;
    case PREF_TURN_SMALL:
        return m_prefs.getTurnSize() == STS_SMALL;
        break;
    case PREF_TURN_MEDIUM:
        return m_prefs.getTurnSize() == STS_MEDIUM;
        break;
    case PREF_TURN_LARGE:
        return m_prefs.getTurnSize() == STS_LARGE;
        break;
    case PREF_DETAIL_MIN:
        return m_prefs.getDetail() == LOD_MIN;
        break;
    case PREF_DETAIL_LOW:
        return m_prefs.getDetail() == LOD_LOW;
        break;
    case PREF_DETAIL_HIGH:
        return m_prefs.getDetail() == LOD_HIGH;
        break;
    case PREF_DETAIL_MAX:
        return m_prefs.getDetail() == LOD_MAX;
        break;
    case PREF_TEXT_WAIT:
        return m_prefs.getTextSpeed() == TS_WAIT;
        break;
    case PREF_TEXT_MEDIUM:
        return m_prefs.getTextSpeed() == TS_MEDIUM;
        break;
    case PREF_TEXT_FAST:
        return m_prefs.getTextSpeed() == TS_FAST;
        break;
    case PREF_SOUND:
        return m_prefs.getSound();
        break;
    case PREF_MUSIC:
        return m_prefs.getMusic();
        break;
    case PREF_COMBAT_MUSIC:
        return m_prefs.getCombatMusic();
        break;
    case PREF_CD_MUSIC:
        return m_prefs.getCdMusic();
        break;
    case PREF_INTRODUCTION:
        return m_prefs.getIntroduction();
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
    return false;
}

void
PreferencesDialogBridge::setSelectState(const unsigned int action)
{
    switch (action)
    {
    case PREF_STEP_SMALL:
        m_prefs.setStepSize(STS_SMALL);
        break;
    case PREF_STEP_MEDIUM:
        m_prefs.setStepSize(STS_MEDIUM);
        break;
    case PREF_STEP_LARGE:
        m_prefs.setStepSize(STS_LARGE);
        break;
    case PREF_TURN_SMALL:
        m_prefs.setTurnSize(STS_SMALL);
        break;
    case PREF_TURN_MEDIUM:
        m_prefs.setTurnSize(STS_MEDIUM);
        break;
    case PREF_TURN_LARGE:
        m_prefs.setTurnSize(STS_LARGE);
        break;
    case PREF_DETAIL_MIN:
        m_prefs.setDetail(LOD_MIN);
        break;
    case PREF_DETAIL_LOW:
        m_prefs.setDetail(LOD_LOW);
        break;
    case PREF_DETAIL_HIGH:
        m_prefs.setDetail(LOD_HIGH);
        break;
    case PREF_DETAIL_MAX:
        m_prefs.setDetail(LOD_MAX);
        break;
    case PREF_TEXT_WAIT:
        m_prefs.setTextSpeed(TS_WAIT);
        break;
    case PREF_TEXT_MEDIUM:
        m_prefs.setTextSpeed(TS_MEDIUM);
        break;
    case PREF_TEXT_FAST:
        m_prefs.setTextSpeed(TS_FAST);
        break;
    case PREF_SOUND:
        m_prefs.setSound(!m_prefs.getSound());
        break;
    case PREF_MUSIC:
        m_prefs.setMusic(!m_prefs.getMusic());
        break;
    case PREF_COMBAT_MUSIC:
        m_prefs.setCombatMusic(!m_prefs.getCombatMusic());
        break;
    case PREF_CD_MUSIC:
        m_prefs.setCdMusic(!m_prefs.getCdMusic());
        break;
    case PREF_INTRODUCTION:
        m_prefs.setIntroduction(!m_prefs.getIntroduction());
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

void
PreferencesDialogBridge::setDefaults()
{
    m_prefs.setDefaults();
}
