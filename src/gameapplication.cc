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

#include "animationresource.h"
#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "fontresource.h"
#include "gameapplication.h"
#include "movieplayer.h"
#include "objectresource.h"
#include "pointermanager.h"
#include "sdl_toolkit.h"
#include "text.h"

GameApplication* GameApplication::m_instance = 0;

GameApplication::GameApplication()
    : m_done ( false )
    , m_inputGrabbed ( false )
    , m_game()
    , m_state ( 0 )
    , m_screenSaveCount ( 0 )
{
    MediaToolkit* media = MediaToolkit::getInstance();
    media->getVideo()->createWindow ( 1 );
    media->getVideo()->setMode ( LORES_HICOL );
    media->getVideo()->clear();

    PaletteResource pal;
    pal.getPalette()->fill();
    pal.getPalette()->activate ( 0, WINDOW_COLORS );
    FontResource fnt;
    FileManager::getInstance()->load ( &fnt, "GAME.FNT" );
    TextBlock txt ( "xBaK: Betrayal at Krondor  A fan-made remake", 15, 0, 0, 0, false );
    txt.draw ( 16, 16, 240, 16, fnt.getFont() );
    media->getVideo()->refresh();

    m_config = new ConfigResource;
    if ( FileManager::getInstance()->configExists ( "krondor.cfg" ) )
    {
        FileManager::getInstance()->load ( m_config, "krondor.cfg" );
    }
    else
    {
        Preferences *prefs = new Preferences();
        prefs->setDefaults();
        m_config->setPreferences ( prefs );
        FileManager::getInstance()->save ( m_config, "krondor.cfg" );
    }
    m_game = new GameResource;
    PointerManager::getInstance()->addPointer ( "POINTER.BMX" );
    PointerManager::getInstance()->addPointer ( "POINTERG.BMX" );

    media->getClock()->delay ( 500 );
}

GameApplication::~GameApplication()
{
    if ( m_config )
    {
        delete m_config;
    }
    if ( m_game )
    {
        delete m_game;
    }
    PointerManager::cleanUp();
    MediaToolkit::cleanUp();
    ObjectResource::cleanUp();
    SoundResource::cleanUp();
    FileManager::cleanUp();
}

GameApplication* GameApplication::getInstance()
{
    if ( !m_instance )
    {
        m_instance = new GameApplication();
    }
    return m_instance;
}

void GameApplication::cleanUp()
{
    GameStateCast::cleanUp();
    GameStateCamp::cleanUp();
    GameStateChapter::cleanUp();
    GameStateCombat::cleanUp();
    GameStateContents::cleanUp();
    GameStateFullMap::cleanUp();
    GameStateInfo::cleanUp();
    GameStateInitialOptions::cleanUp();
    GameStateIntro::cleanUp();
    GameStateInventory::cleanUp();
    GameStateLoad::cleanUp();
    GameStateMap::cleanUp();
    GameStateOptions::cleanUp();
    GameStatePreferences::cleanUp();
    GameStateSave::cleanUp();
    GameStateWorld::cleanUp();
    if ( m_instance )
    {
        delete m_instance;
        m_instance = 0;
    }
}

Preferences * GameApplication::getPreferences()
{
    return m_config->getPreferences();
}

Game * GameApplication::getGame()
{
    return m_game->getGame();
}

void GameApplication::setState ( GameState *st )
{
    m_state = st;
}

void GameApplication::playIntro()
{
    try
    {
        AnimationResource anim;
        FileManager::getInstance()->load ( &anim, "INTRO.ADS" );
        MovieResource ttm;
        FileManager::getInstance()->load ( &ttm, anim.getAnimationData ( 1 ).m_resource );
        MoviePlayer moviePlayer;
        moviePlayer.play ( &ttm.getMovieChunks(), true );
    }
    catch ( Exception &e )
    {
        e.print ( "GameApplication::playIntro" );
    }
}

void GameApplication::startNewGame()
{
    FileManager::getInstance()->load ( m_game, "startup.gam" );
    m_game->getGame()->getParty()->activateMember ( 0, 0 );
    m_game->getGame()->getParty()->activateMember ( 1, 2 );
    m_game->getGame()->getParty()->activateMember ( 2, 1 );
    m_game->getGame()->getCamera()->setPosition ( Vector2D ( 669600, 1064800 ) );
    m_game->getGame()->getCamera()->setHeading ( SOUTH );
}

void GameApplication::quitGame()
{
    m_done = true;
}

void GameApplication::saveConfig()
{
    FileManager::getInstance()->save ( m_config, "krondor.cfg" );
}

void GameApplication::run()
{
    try
    {
        m_state = GameStateIntro::getInstance();
        MediaToolkit::getInstance()->addKeyboardListener ( this );
        MediaToolkit::getInstance()->addPointerButtonListener ( this );
        MediaToolkit::getInstance()->addTimerListener ( this );
        m_state->enter();
        GameState *savedState = m_state;
        m_done = false;
        while ( !m_done )
        {
            if ( m_state != savedState )
            {
                savedState->leave();
                m_state->enter();
                savedState = m_state;
            }
            m_state->execute();
        }
        savedState->leave();
        MediaToolkit::getInstance()->removeKeyboardListener ( this );
        MediaToolkit::getInstance()->removePointerButtonListener ( this );
        MediaToolkit::getInstance()->removeTimerListener ( this );
    }
    catch ( Exception &e )
    {
        e.print ( "GameApplication::run" );
    }
}

void GameApplication::keyPressed ( const KeyboardEvent& kbe )
{
    switch ( kbe.getKey() )
    {
    case KEY_F11:
    {
        m_screenSaveCount++;
        std::stringstream filenameStream;
        filenameStream << Directories::getInstance()->getCapturePath();
        filenameStream << "xbak_" << std::setw ( 3 ) << std::setfill ( '0' ) << m_screenSaveCount << ".bmp";
        MediaToolkit::getInstance()->getVideo()->saveScreenShot ( filenameStream.str() );
    }
    break;
    case KEY_F12:
        m_inputGrabbed = !m_inputGrabbed;
        MediaToolkit::getInstance()->getVideo()->grabInput ( m_inputGrabbed );
        break;
    default:
        break;
    }
}

void GameApplication::keyReleased ( const KeyboardEvent& kbe )
{
    switch ( kbe.getKey() )
    {
    default:
        break;
    }
}

void GameApplication::pointerButtonPressed ( const PointerButtonEvent& pbe )
{
    switch ( pbe.getButton() )
    {
    case PB_PRIMARY:
    case PB_SECONDARY:
        if ( !m_inputGrabbed )
        {
            m_inputGrabbed = true;
            MediaToolkit::getInstance()->getVideo()->grabInput ( true );
        }
        break;
    case PB_TERTIARY:
        if ( m_inputGrabbed )
        {
            m_inputGrabbed = false;
            MediaToolkit::getInstance()->getVideo()->grabInput ( false );
        }
        break;
    default:
        break;
    }
}

void GameApplication::pointerButtonReleased ( const PointerButtonEvent& pbe )
{
    switch ( pbe.getButton() )
    {
    default:
        break;
    }
}

void GameApplication::timerExpired ( const TimerEvent& te )
{
    if ( te.getId() == TMR_MOVING )
    {
        m_state->move();
    }
    if ( te.getId() == TMR_TURNING )
    {
        m_state->turn();
    }
}
