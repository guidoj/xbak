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

#include <cstring>

#include "exception.h"
#include "filemanager.h"
#include "movieplayer.h"
#include "pointermanager.h"

const unsigned int SAVE_BACKGROUND    = 0x0020;
const unsigned int DRAW_BACKGROUND    = 0x0080;
const unsigned int PURGE              = 0x0110;
const unsigned int UPDATE             = 0x0ff0;
const unsigned int DELAY              = 0x1020;
const unsigned int SLOT_IMAGE         = 0x1050;
const unsigned int SLOT_PALETTE       = 0x1060;
const unsigned int SET_SCENE          = 0x1110;
const unsigned int SET_FRAME0         = 0x2000;
const unsigned int SET_FRAME1         = 0x2010;
const unsigned int FADE_OUT           = 0x4110;
const unsigned int FADE_IN            = 0x4120;
const unsigned int SAVE_IMAGE0        = 0x4200;
const unsigned int SAVE_IMAGE1        = 0x4210;
const unsigned int SET_WINDOW         = 0xa100;
const unsigned int DRAW_SPRITE0       = 0xa500;
const unsigned int DRAW_SPRITE1       = 0xa510;
const unsigned int DRAW_SPRITE2       = 0xa520;
const unsigned int DRAW_SPRITE3       = 0xa530;
const unsigned int DRAW_SCREEN        = 0xb600;
const unsigned int LOAD_SOUNDRESOURCE = 0xc020;
const unsigned int SELECT_SOUND       = 0xc030;
const unsigned int DESELECT_SOUND     = 0xc040;
const unsigned int PLAY_SOUND         = 0xc050;
const unsigned int STOP_SOUND         = 0xc060;
const unsigned int LOAD_SCREEN        = 0xf010;
const unsigned int LOAD_IMAGE         = 0xf020;
const unsigned int LOAD_PALETTE       = 0xf050;

MoviePlayer::MoviePlayer()
{
    MediaToolkit::getInstance()->addKeyboardListener ( this );
    MediaToolkit::getInstance()->addPointerButtonListener ( this );
    MediaToolkit::getInstance()->addTimerListener ( this );
}

MoviePlayer::~MoviePlayer()
{
    MediaToolkit::getInstance()->removeKeyboardListener ( this );
    MediaToolkit::getInstance()->removePointerButtonListener ( this );
    MediaToolkit::getInstance()->removeTimerListener ( this );
}

void MoviePlayer::play ( std::vector<MovieChunk *> *movie, const bool repeat )
{
    try
    {
        m_chunkVec = movie;
        m_looped = repeat;
        m_delayed = false;
        m_playing = true;
        m_screenSlot = 0;
        m_soundSlot = SoundResource::getInstance();
        memset ( m_imageSlot, 0, sizeof ( ImageResource* ) * MAX_IMAGE_SLOTS );
        memset ( m_paletteSlot, 0, sizeof ( Palette* ) * MAX_PALETTE_SLOTS );
        m_backgroundImage = 0;
        m_backgroundImageDrawn = false;
        m_savedImage = 0;
        m_savedImageDrawn = false;
        m_currFrame = 0;
        m_currImage = 0;
        m_currPalette = 0;
        m_currChunk = 0;
        m_currDelay = 0;
        m_currSound = 0;
        m_soundMap.clear();
        m_paletteSlot[m_currPalette] = new PaletteResource;
        m_paletteSlot[m_currPalette]->getPalette()->retrieve ( 0, PALETTE_COLORS );
        m_paletteActivated = false;

        PointerManager::getInstance()->getCurrentPointer()->setVisible ( false );

        while ( m_playing )
        {
            playChunk ( MediaToolkit::getInstance() );
            if ( m_playing )
            {
                MediaToolkit::getInstance()->waitEvents();
            }
        }
        if ( m_delayed )
        {
            MediaToolkit::getInstance()->getClock()->stopTimer ( TMR_MOVIE_PLAYER );
        }
        m_paletteSlot[m_currPalette]->getPalette()->fadeOut ( 0, PALETTE_COLORS, 64, 5 );

        PointerManager::getInstance()->getCurrentPointer()->setVisible ( true );

        if ( m_backgroundImage != 0 )
        {
            delete m_backgroundImage;
            m_backgroundImage = 0;
        }
        if ( m_savedImage != 0 )
        {
            delete m_savedImage;
            m_savedImage = 0;
        }
        if ( m_screenSlot != 0 )
        {
            delete m_screenSlot;
        }
        for ( unsigned int i = 0; i < MAX_IMAGE_SLOTS; i++ )
        {
            if ( m_imageSlot[i] != 0 )
            {
                delete m_imageSlot[i];
            }
        }
        for ( unsigned int i = 0; i < MAX_PALETTE_SLOTS; i++ )
        {
            if ( m_paletteSlot[i] != 0 )
            {
                delete m_paletteSlot[i];
            }
        }
    }
    catch ( Exception &e )
    {
        e.print ( "MoviePlayer::Play" );
        throw;
    }
}

void MoviePlayer::playChunk ( MediaToolkit* media )
{
    try
    {
        while ( ( m_playing ) && ( !m_delayed ) )
        {
            MovieChunk *mc = ( *m_chunkVec ) [m_currChunk];
            switch ( mc->code )
            {
            case SAVE_BACKGROUND:
                if ( m_backgroundImage == 0 )
                {
                    m_backgroundImage = new Image ( WINDOW_WIDTH, WINDOW_HEIGHT );
                }
                m_backgroundImage->read ( 0, 0 );
                m_backgroundImageDrawn = false;
                break;
            case DRAW_BACKGROUND:
                if ( m_backgroundImage != 0 )
                {
                    m_backgroundImage->draw ( 0, 0 );
                    m_backgroundImageDrawn = true;
                }
                break;
            case PURGE:
                if ( m_backgroundImage != 0 )
                {
                    delete m_backgroundImage;
                    m_backgroundImage = 0;
                }
                if ( m_savedImage != 0 )
                {
                    delete m_savedImage;
                    m_savedImage = 0;
                }
                break;
            case UPDATE:
                if ( ( m_backgroundImage != 0 ) && ( !m_backgroundImageDrawn ) )
                {
                    m_backgroundImage->draw ( 0, 0 );
                    m_backgroundImageDrawn = true;
                }
                if ( ( m_savedImage != 0 ) && ( !m_savedImageDrawn ) )
                {
                    m_savedImage->draw ( m_xSavedImage, m_ySavedImage );
                    m_savedImageDrawn = true;
                }
                if ( !m_paletteActivated )
                {
                    m_paletteSlot[m_currPalette]->getPalette()->activate ( 0, PALETTE_COLORS );
                    m_paletteActivated = true;
                }
                media->getVideo()->refresh();
                if ( m_currDelay > 0 )
                {
                    m_delayed = true;
                    media->getClock()->startTimer ( TMR_MOVIE_PLAYER, m_currDelay );
                }
                m_backgroundImageDrawn = false;
                m_savedImageDrawn = false;
                break;
            case DELAY:
                m_currDelay = mc->data[0] * 10;
                break;
            case SLOT_IMAGE:
                m_currImage = mc->data[0];
                break;
            case SLOT_PALETTE:
                m_currPalette = mc->data[0];
                m_paletteActivated = false;
                break;
            case SET_SCENE:
                break;
            case SET_FRAME0:
            case SET_FRAME1:
                m_currFrame = mc->data[1];
                break;
            case FADE_OUT:
                m_paletteSlot[m_currPalette]->getPalette()->fadeOut ( mc->data[0], mc->data[1], 64 << ( mc->data[2] & 0x0f ), 2 << mc->data[3] );
                media->getVideo()->clear();
                m_paletteActivated = true;
                break;
            case FADE_IN:
                m_paletteSlot[m_currPalette]->getPalette()->fadeIn ( mc->data[0], mc->data[1], 64 << ( mc->data[2] & 0x0f ), 2 << mc->data[3] );
                m_paletteActivated = true;
                break;
            case SAVE_IMAGE0:
            case SAVE_IMAGE1:
                if ( m_savedImage != 0 )
                {
                    delete m_savedImage;
                }
                m_xSavedImage = mc->data[0];
                m_ySavedImage = mc->data[1];
                m_savedImage = new Image ( mc->data[2], mc->data[3] );
                m_savedImage->read ( m_xSavedImage, m_ySavedImage );
                m_savedImageDrawn = false;
                break;
            case SET_WINDOW:
                break;
            case DRAW_SPRITE0:
            case DRAW_SPRITE1:
            case DRAW_SPRITE2:
            case DRAW_SPRITE3:
                if ( ( m_backgroundImage != 0 ) && ( !m_backgroundImageDrawn ) )
                {
                    m_backgroundImage->draw ( 0, 0 );
                    m_backgroundImageDrawn = true;
                }
                if ( ( m_savedImage != 0 ) && ( !m_savedImageDrawn ) )
                {
                    m_savedImage->draw ( m_xSavedImage, m_ySavedImage );
                    m_savedImageDrawn = true;
                }
                if ( m_imageSlot[mc->data[3]] )
                {
                    m_imageSlot[mc->data[3]]->getImage ( mc->data[2] )->draw ( mc->data[0], mc->data[1], 0 );
                }
                break;
            case DRAW_SCREEN:
                if ( ( m_backgroundImage != 0 ) && ( !m_backgroundImageDrawn ) )
                {
                    m_backgroundImage->draw ( 0, 0 );
                    m_backgroundImageDrawn = true;
                }
                if ( m_screenSlot )
                {
                    m_screenSlot->getImage()->draw ( mc->data[0], mc->data[1] );
                }
                break;
            case LOAD_SOUNDRESOURCE:
                break;
            case SELECT_SOUND:
            {
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( mc->data[0] );
                if ( it != m_soundMap.end() )
                {
                    if ( it->second >= 0 )
                    {
                        media->getAudio()->stopSound ( it->second );
                    }
                    m_soundMap.erase ( it );
                }
                m_soundMap.insert ( std::pair<unsigned int, int> ( mc->data[0], -1 ) );
            }
            break;
            case DESELECT_SOUND:
            {
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( mc->data[0] );
                if ( it != m_soundMap.end() )
                {
                    if ( it->second >= 0 )
                    {
                        media->getAudio()->stopSound ( it->second );
                    }
                    m_soundMap.erase ( it );
                }
            }
            break;
            case PLAY_SOUND:
            {
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( mc->data[0] );
                if ( it != m_soundMap.end() )
                {
                    SoundData data = m_soundSlot->getSoundData ( it->first );
                    if ( it->second >= 0 )
                    {
                        if (data.type == SND_TYPE_MIDI)
                        {
                            media->getAudio()->stopMusic();
                        }
                        else
                        {
                            media->getAudio()->stopSound ( it->second );
                        }
                    }
                    if (data.type == SND_TYPE_MIDI)
                    {
                        it->second = media->getAudio()->playMusic ( data.sounds[0]->getSamples() );
                    }
                    else{
                        it->second = media->getAudio()->playSound ( data.sounds[0]->getSamples() );
                    }
                }
            }
            break;
            case STOP_SOUND:
            {
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( mc->data[0] );
                if ( it != m_soundMap.end() )
                {
                    SoundData data = m_soundSlot->getSoundData ( it->first );
                    if ( it->second >= 0 )
                    {
                        if (data.type == SND_TYPE_MIDI)
                        {
                            media->getAudio()->stopMusic();
                        }
                        else
                        {
                            media->getAudio()->stopSound ( it->second );
                        }
                    }
                    m_soundMap.erase ( it );
                }
            }
            break;
            case LOAD_SCREEN:
                if ( m_screenSlot )
                {
                    delete m_screenSlot;
                }
                mc->name[mc->name.length() - 1] = 'X';
                m_screenSlot = new ScreenResource;
                FileManager::getInstance()->load ( m_screenSlot, mc->name );
                m_screenSlot->getImage()->draw ( 0, 0 );
                break;
            case LOAD_IMAGE:
                if ( m_imageSlot[m_currImage] )
                {
                    delete m_imageSlot[m_currImage];
                }
                mc->name[mc->name.length() - 1] = 'X';
                m_imageSlot[m_currImage] = new ImageResource;
                FileManager::getInstance()->load ( m_imageSlot[m_currImage], mc->name );
                break;
            case LOAD_PALETTE:
                if ( m_paletteSlot[m_currPalette] )
                {
                    delete m_paletteSlot[m_currPalette];
                }
                m_paletteSlot[m_currPalette] = new PaletteResource;
                FileManager::getInstance()->load ( m_paletteSlot[m_currPalette], mc->name );
                m_paletteActivated = false;
                break;
            default:
                break;
            }
            m_currChunk++;
            if ( m_currChunk == m_chunkVec->size() )
            {
                if ( m_looped )
                {
                    m_currChunk = 0;
                    if ( m_backgroundImage != 0 )
                    {
                        delete m_backgroundImage;
                        m_backgroundImage = 0;
                    }
                    if ( m_savedImage != 0 )
                    {
                        delete m_savedImage;
                        m_savedImage = 0;
                    }
                }
                else
                {
                    m_playing = false;
                }
            }
        }
    }
    catch ( Exception &e )
    {
        e.print ( "MoviePlayer::PlayChunk" );
        throw;
    }
}

void MoviePlayer::keyPressed ( const KeyboardEvent& kbe )
{
    switch ( kbe.getKey() )
    {
    case KEY_ESCAPE:
    case KEY_RETURN:
    case KEY_SPACE:
        m_playing = false;
        break;
    default:
        break;
    }
}

void MoviePlayer::keyReleased ( const KeyboardEvent& kbe )
{
    switch ( kbe.getKey() )
    {
    default:
        break;
    }
}

void MoviePlayer::pointerButtonPressed ( const PointerButtonEvent& pbe )
{
    switch ( pbe.getButton() )
    {
    case PB_PRIMARY:
        m_playing = false;
        break;
    default:
        break;
    }
}

void MoviePlayer::pointerButtonReleased ( const PointerButtonEvent& pbe )
{
    switch ( pbe.getButton() )
    {
    default:
        break;
    }
}

void MoviePlayer::timerExpired ( const TimerEvent& te )
{
    if ( te.getId() == TMR_MOVIE_PLAYER )
    {
        m_delayed = false;
    }
}
