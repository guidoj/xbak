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

#include <iomanip>
#include <sstream>

#include "exception.h"
#include "gameapplication.h"
#include "gamestate.h"
#include "preferencesdialogbridge.h"

GameState::GameState()
    : m_gameApp(GameApplication::getInstance())
    , m_dialogFactory()
    , m_prevState(0)
{
}

GameState::~GameState()
{
}

void
GameState::changeState(GameState *state, const bool savePreviousState)
{
    if (savePreviousState)
    {
        state->m_prevState = this;
    }
    m_gameApp->setState(state);
}

void
GameState::move()
{
}

void
GameState::turn()
{
}

GameStateCamp* GameStateCamp::m_instance = 0;

GameStateCamp::GameStateCamp()
{
    m_dialog = m_dialogFactory.createCampDialog();
}

GameStateCamp::~GameStateCamp()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateCamp*
GameStateCamp::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateCamp();
    }
    return m_instance;
}

void
GameStateCamp::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateCamp::enter()
{
    m_dialog->enter();
}

void
GameStateCamp::leave()
{
    m_dialog->leave();
}

void
GameStateCamp::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case CAMP_EXIT:
        changeState(m_prevState);
        break;
    case ACT_STOP:
    case CAMP_UNTIL_HEALED:
    case CAMP_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateCast* GameStateCast::m_instance = 0;

GameStateCast::GameStateCast()
    : m_dialog(0)
{
}

GameStateCast::~GameStateCast()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateCast*
GameStateCast::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateCast();
    }
    return m_instance;
}

void
GameStateCast::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateCast::enter()
{
    m_dialog = m_dialogFactory.createCastDialog();
    m_dialog->enter();
}

void
GameStateCast::leave()
{
    m_dialog->leave();
    delete m_dialog;
    m_dialog = 0;
}

void
GameStateCast::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case CAST_EXIT:
        changeState(GameStateWorld::getInstance());
        break;
    case CAST_CAMP1:
    case CAST_CAMP2:
        changeState(GameStateCamp::getInstance(), true);
        break;
    case CAST_MEMBER1:
        m_gameApp->getGame()->getParty()->selectMember(0);
        break;
    case CAST_MEMBER2:
        m_gameApp->getGame()->getParty()->selectMember(1);
        break;
    case CAST_MEMBER3:
        m_gameApp->getGame()->getParty()->selectMember(2);
        break;
    case CAST_MEMBER1 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case CAST_MEMBER2 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(1);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case CAST_MEMBER3 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(2);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case ACT_STOP:
    case ACT_UP:
    case ACT_DOWN:
    case ACT_LEFT:
    case ACT_RIGHT:
    case CAST_TRIANGLE:
    case CAST_SQUARE:
    case CAST_CAST:
    case CAST_BOOKMARK:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateChapter* GameStateChapter::m_instance = 0;

GameStateChapter::GameStateChapter()
{
}

GameStateChapter::~GameStateChapter()
{
}

GameStateChapter*
GameStateChapter::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateChapter();
    }
    return m_instance;
}

void
GameStateChapter::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateChapter::enter()
{
}

void
GameStateChapter::leave()
{
}

void
GameStateChapter::execute()
{
    m_gameApp->getGame()->getChapter()->start();
    changeState(GameStateWorld::getInstance());
}

GameStateCombat* GameStateCombat::m_instance = 0;

GameStateCombat::GameStateCombat()
{
}

GameStateCombat::~GameStateCombat()
{
}

GameStateCombat*
GameStateCombat::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateCombat();
    }
    return m_instance;
}

void
GameStateCombat::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateCombat::enter()
{
}

void
GameStateCombat::leave()
{
}

void
GameStateCombat::execute()
{
    changeState(GameStateWorld::getInstance());
}

GameStateContents* GameStateContents::m_instance = 0;

GameStateContents::GameStateContents()
{
    m_dialog = m_dialogFactory.createContentsDialog();
}

GameStateContents::~GameStateContents()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateContents*
GameStateContents::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateContents();
    }
    return m_instance;
}

void
GameStateContents::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateContents::enter()
{
    m_dialog->enter();
}

void
GameStateContents::leave()
{
    m_dialog->leave();
}

void
GameStateContents::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case CONT_EXIT:
        changeState(m_prevState);
        break;
    case ACT_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateFullMap* GameStateFullMap::m_instance = 0;

GameStateFullMap::GameStateFullMap()
{
    m_dialog = m_dialogFactory.createFullMapDialog();
}

GameStateFullMap::~GameStateFullMap()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateFullMap*
GameStateFullMap::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateFullMap();
    }
    return m_instance;
}

void
GameStateFullMap::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateFullMap::enter()
{
    m_dialog->enter();
}

void
GameStateFullMap::leave()
{
    m_dialog->leave();
}

void
GameStateFullMap::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case FMAP_EXIT:
        changeState(GameStateMap::getInstance());
        break;
    case ACT_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateInfo* GameStateInfo::m_instance = 0;

GameStateInfo::GameStateInfo()
    : m_dialog(0)
{
}

GameStateInfo::~GameStateInfo()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateInfo*
GameStateInfo::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateInfo();
    }
    return m_instance;
}

void
GameStateInfo::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateInfo::enter()
{
    m_dialog = m_dialogFactory.createInfoDialog();
    m_dialog->enter();
}

void
GameStateInfo::leave()
{
    m_dialog->leave();
    delete m_dialog;
    m_dialog = 0;
}

void
GameStateInfo::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case INFO_EXIT:
        changeState(m_prevState);
        break;
    case ACT_STOP:
    case ACT_UP:
    case ACT_DOWN:
    case ACT_LEFT:
    case ACT_RIGHT:
    case INFO_SPELLS:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateInitialOptions* GameStateInitialOptions::m_instance = 0;

GameStateInitialOptions::GameStateInitialOptions()
{
    m_dialog = m_dialogFactory.createOptionsDialog(true);
}

GameStateInitialOptions::~GameStateInitialOptions()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateInitialOptions*
GameStateInitialOptions::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateInitialOptions();
    }
    return m_instance;
}

void
GameStateInitialOptions::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateInitialOptions::enter()
{
    m_dialog->enter();
}

void
GameStateInitialOptions::leave()
{
    m_dialog->leave();
}

void
GameStateInitialOptions::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case OPT_QUIT:
        m_gameApp->quitGame();
        break;
    case OPT_NEW_GAME:
        m_gameApp->startNewGame();
        changeState(GameStateChapter::getInstance());
        break;
    case OPT_CONTENTS:
        changeState(GameStateContents::getInstance(), true);
        break;
    case OPT_PREFERENCES:
        changeState(GameStatePreferences::getInstance(), true);
        break;
    case OPT_RESTORE:
        changeState(GameStateLoad::getInstance(), true);
        break;
    case ACT_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateIntro* GameStateIntro::m_instance = 0;

GameStateIntro::GameStateIntro()
{
}

GameStateIntro::~GameStateIntro()
{
}

GameStateIntro*
GameStateIntro::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateIntro();
    }
    return m_instance;
}

void
GameStateIntro::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateIntro::enter()
{
}

void
GameStateIntro::leave()
{
}

void
GameStateIntro::execute()
{
    if (m_gameApp->getPreferences()->getIntroduction())
    {
        m_gameApp->playIntro();
    }
    changeState(GameStateInitialOptions::getInstance());
}

GameStateInventory* GameStateInventory::m_instance = 0;

GameStateInventory::GameStateInventory()
    : m_dialog(0)
{
}

GameStateInventory::~GameStateInventory()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateInventory*
GameStateInventory::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateInventory();
    }
    return m_instance;
}

void
GameStateInventory::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateInventory::enter()
{
    m_dialog = m_dialogFactory.createInventoryDialog();
    m_dialog->enter();
}

void
GameStateInventory::leave()
{
    m_dialog->leave();
    delete m_dialog;
    m_dialog = 0;
}

void
GameStateInventory::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case INV_EXIT:
        changeState(m_prevState);
        break;
    case INV_MEMBER1:
        m_gameApp->getGame()->getParty()->selectMember(0);
        break;
    case INV_MEMBER2:
        m_gameApp->getGame()->getParty()->selectMember(1);
        break;
    case INV_MEMBER3:
        m_gameApp->getGame()->getParty()->selectMember(2);
        break;
    case INV_MEMBER1 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case INV_MEMBER2 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(1);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case INV_MEMBER3 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(2);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case ACT_STOP:
    case ACT_UP:
    case ACT_DOWN:
    case ACT_LEFT:
    case ACT_RIGHT:
    case INV_UNKNOWN:
    case INV_MORE_INFO:
        break;
    default:
        if ((action >= INVENTORY_OFFSET) && (action < 2 * INVENTORY_OFFSET))
        {
            // TODO
        }
        else
        {
            throw UnexpectedValue(__FILE__, __LINE__, action);
        }
        break;
    }
}

GameStateLoad* GameStateLoad::m_instance = 0;

GameStateLoad::GameStateLoad()
{
    m_dialog = m_dialogFactory.createLoadDialog();
}

GameStateLoad::~GameStateLoad()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateLoad*
GameStateLoad::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateLoad();
    }
    return m_instance;
}

void
GameStateLoad::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateLoad::enter()
{
    m_dialog->enter();
}

void
GameStateLoad::leave()
{
    m_dialog->leave();
}

void
GameStateLoad::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case LOAD_CANCEL:
        changeState(m_prevState);
        break;
    case LOAD_RESTORE:
        changeState(m_prevState);
        break;
    case ACT_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateMap* GameStateMap::m_instance = 0;

GameStateMap::GameStateMap()
    : m_dialog(0)
{
}

GameStateMap::~GameStateMap()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateMap*
GameStateMap::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateMap();
    }
    return m_instance;
}

void
GameStateMap::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateMap::enter()
{
    m_gameApp->getGame()->getParty()->selectMember(-1);
    m_dialog = m_dialogFactory.createMapDialog();
    m_dialog->enter();
}

void
GameStateMap::leave()
{
    m_dialog->leave();
    delete m_dialog;
    m_dialog = 0;
}

void
GameStateMap::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case MAP_MAIN:
        changeState(GameStateWorld::getInstance());
        break;
    case MAP_CAMP:
        changeState(GameStateCamp::getInstance(), true);
        break;
    case MAP_FULLMAP:
        changeState(GameStateFullMap::getInstance());
        break;
    case MAP_MEMBER1:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInventory::getInstance(), true);
        break;
    case MAP_MEMBER2:
        m_gameApp->getGame()->getParty()->selectMember(1);
        changeState(GameStateInventory::getInstance(), true);
        break;
    case MAP_MEMBER3:
        m_gameApp->getGame()->getParty()->selectMember(2);
        changeState(GameStateInventory::getInstance(), true);
        break;
    case MAP_MEMBER1 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case MAP_MEMBER2 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case MAP_MEMBER3 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case ACT_STOP:
    case ACT_UP:
    case MAP_UP:
    case ACT_DOWN:
    case MAP_DOWN:
    case ACT_LEFT:
    case MAP_LEFT:
    case ACT_RIGHT:
    case MAP_RIGHT:
    case MAP_ZOOMIN:
    case MAP_ZOOMOUT:
    case MAP_UNKNOWN:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateOptions* GameStateOptions::m_instance = 0;

GameStateOptions::GameStateOptions()
{
    m_dialog = m_dialogFactory.createOptionsDialog(false);
}

GameStateOptions::~GameStateOptions()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateOptions*
GameStateOptions::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateOptions();
    }
    return m_instance;
}

void
GameStateOptions::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateOptions::enter()
{
    m_dialog->enter();
}

void
GameStateOptions::leave()
{
    m_dialog->leave();
}

void
GameStateOptions::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case OPT_QUIT:
        m_gameApp->quitGame();
        break;
    case OPT_NEW_GAME:
        m_gameApp->startNewGame();
        changeState(GameStateChapter::getInstance());
        break;
    case OPT_CANCEL:
        changeState(GameStateWorld::getInstance());
        break;
    case OPT_CONTENTS:
        changeState(GameStateContents::getInstance(), true);
        break;
    case OPT_PREFERENCES:
        changeState(GameStatePreferences::getInstance(), true);
        break;
    case OPT_RESTORE:
        changeState(GameStateLoad::getInstance(), true);
        break;
    case OPT_SAVE:
        changeState(GameStateSave::getInstance(), true);
        break;
    case ACT_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStatePreferences* GameStatePreferences::m_instance = 0;

GameStatePreferences::GameStatePreferences()
{
    m_dialog = m_dialogFactory.createPreferencesDialog();
}

GameStatePreferences::~GameStatePreferences()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStatePreferences*
GameStatePreferences::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStatePreferences();
    }
    return m_instance;
}

void
GameStatePreferences::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
    PreferencesDialogBridge::cleanUp();
}

void
GameStatePreferences::enter()
{
    PreferencesDialogBridge::getInstance()->fetch();
    m_dialog->enter();
}

void
GameStatePreferences::leave()
{
    m_dialog->leave();
}

void
GameStatePreferences::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case PREF_CANCEL:
        changeState(m_prevState);
        break;
    case PREF_OK:
        PreferencesDialogBridge::getInstance()->commit();
        m_gameApp->saveConfig();
        changeState(m_prevState);
        break;
    case PREF_DEFAULTS:
        PreferencesDialogBridge::getInstance()->setDefaults();
        break;
    case PREF_STEP_SMALL:
    case PREF_STEP_MEDIUM:
    case PREF_STEP_LARGE:
    case PREF_TURN_SMALL:
    case PREF_TURN_MEDIUM:
    case PREF_TURN_LARGE:
    case PREF_DETAIL_MIN:
    case PREF_DETAIL_LOW:
    case PREF_DETAIL_HIGH:
    case PREF_DETAIL_MAX:
    case PREF_TEXT_WAIT:
    case PREF_TEXT_MEDIUM:
    case PREF_TEXT_FAST:
    case PREF_SOUND:
    case PREF_MUSIC:
    case PREF_COMBAT_MUSIC:
    case PREF_CD_MUSIC:
    case PREF_INTRODUCTION:
        PreferencesDialogBridge::getInstance()->setSelectState(action);
        break;
    case ACT_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateSave* GameStateSave::m_instance = 0;

GameStateSave::GameStateSave()
{
    m_dialog = m_dialogFactory.createSaveDialog();
}

GameStateSave::~GameStateSave()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateSave*
GameStateSave::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateSave();
    }
    return m_instance;
}

void
GameStateSave::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateSave::enter()
{
    m_dialog->enter();
}

void
GameStateSave::leave()
{
    m_dialog->leave();
}

void
GameStateSave::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case SAVE_CANCEL:
        changeState(m_prevState);
        break;
    case SAVE_SAVE:
        changeState(m_prevState);
        break;
    case SAVE_REMOVE_GAME:
        break;
    case SAVE_REMOVE_DIR:
        break;
    case ACT_STOP:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

GameStateWorld* GameStateWorld::m_instance = 0;

GameStateWorld::GameStateWorld()
    : m_dialog(0)
    , m_moving(0)
    , m_turning(0)
{
}

GameStateWorld::~GameStateWorld()
{
    if (m_dialog)
    {
        delete m_dialog;
    }
}

GameStateWorld*
GameStateWorld::getInstance()
{
    if (!m_instance)
    {
        m_instance = new GameStateWorld();
    }
    return m_instance;
}

void
GameStateWorld::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
GameStateWorld::enter()
{
    m_gameApp->getGame()->getParty()->selectMember(-1);
    m_dialog = m_dialogFactory.createWorldDialog();
    m_dialog->enter();
}

void
GameStateWorld::leave()
{
    m_dialog->leave();
    delete m_dialog;
    m_dialog = 0;
}

void
GameStateWorld::execute()
{
    int action = m_dialog->execute();
    switch (action)
    {
    case ACT_ESCAPE:
    case MAIN_OPTIONS:
        changeState(GameStateOptions::getInstance());
        break;
    case MAIN_CAMP:
        changeState(GameStateCamp::getInstance(), true);
        break;
    case MAIN_CAST:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateCast::getInstance());
        break;
    case MAIN_MAP:
        changeState(GameStateMap::getInstance());
        break;
    case MAIN_MEMBER1:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInventory::getInstance(), true);
        break;
    case MAIN_MEMBER2:
        m_gameApp->getGame()->getParty()->selectMember(1);
        changeState(GameStateInventory::getInstance(), true);
        break;
    case MAIN_MEMBER3:
        m_gameApp->getGame()->getParty()->selectMember(2);
        changeState(GameStateInventory::getInstance(), true);
        break;
    case MAIN_MEMBER1 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(0);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case MAIN_MEMBER2 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(1);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case MAIN_MEMBER3 + RIGHT_CLICK_OFFSET:
        m_gameApp->getGame()->getParty()->selectMember(2);
        changeState(GameStateInfo::getInstance(), true);
        break;
    case ACT_STOP:
        m_moving = 0;
        m_turning = 0;
        break;
    case ACT_LEFT:
    case MAIN_LEFT:
        m_turning = TURN_LEFT;
        turn();
        break;
    case ACT_RIGHT:
    case MAIN_RIGHT:
        m_turning = TURN_RIGHT;
        turn();
        break;
    case ACT_UP:
    case MAIN_UP:
        m_moving = MOVE_FORWARD;
        move();
        break;
    case ACT_DOWN:
    case MAIN_DOWN:
        m_moving = MOVE_BACKWARD;
        move();
        break;
    case MAIN_BOOKMARK:
    case MAIN_UNKNOWN:
        break;
    default:
        throw UnexpectedValue(__FILE__, __LINE__, action);
        break;
    }
}

void
GameStateWorld::move()
{
    if (m_moving != 0)
    {
        m_gameApp->getGame()->getCamera()->move(m_moving * (1 + (int)m_gameApp->getPreferences()->getStepSize()));
        m_dialog->update();
        MediaToolkit::getInstance()->getClock()->startTimer(TMR_MOVING, 100);
    }
}

void
GameStateWorld::turn()
{
    if (m_turning != 0)
    {
        m_gameApp->getGame()->getCamera()->turn(m_turning * (1 + (int)m_gameApp->getPreferences()->getTurnSize()));
        m_dialog->update();
        MediaToolkit::getInstance()->getClock()->startTimer(TMR_TURNING, 100);
    }
}
