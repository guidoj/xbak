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
const unsigned int COMMENT            = 0x1110;
const unsigned int DRAW_SCREEN        = 0x2000;
const unsigned int PREDRAW_SCREEN     = 0x2010;
const unsigned int FADE_OUT           = 0x4110;
const unsigned int FADE_IN            = 0x4120;
const unsigned int SAVE_IMAGE0        = 0x4200;
const unsigned int SAVE_IMAGE1        = 0x4210;
const unsigned int CLEAR_WINDOW       = 0xa100;
const unsigned int DRAW_IMAGE0        = 0xa500;
const unsigned int DRAW_IMAGE1        = 0xa510;
const unsigned int DRAW_IMAGE2        = 0xa520;
const unsigned int DRAW_IMAGE3        = 0xa530;
const unsigned int REDRAW_SCREEN      = 0xb600;
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

void MoviePlayer::play ( std::vector<MovieTag *> *movie, const bool repeat )
{
    try
    {
        m_movieTags = movie;
        m_looped = repeat;
        m_delayed = false;
        m_prerunning = true;
        m_playing = false;
        m_screenSlot = 0;
        m_soundSlot = SoundResource::getInstance();
        memset ( m_imageSlot, 0, sizeof ( ImageResource* ) * MAX_IMAGE_SLOTS );
        memset ( m_paletteSlot, 0, sizeof ( Palette* ) * MAX_PALETTE_SLOTS );
        m_backgroundImage = 0;
        m_backgroundImageDrawn = false;
        m_savedImage = 0;
        m_savedImageDrawn = false;
        m_prerunTag = 0;
        m_currTag = 0;
        m_currImage = 0;
        m_currPalette = 0;
        m_currDelay = 0;
        m_currSound = 0;
        m_soundMap.clear();
        m_paletteSlot[m_currPalette] = new PaletteResource;
        m_paletteSlot[m_currPalette]->getPalette()->retrieve ( 0, PALETTE_COLORS );
        m_paletteActivated = false;

        PointerManager::getInstance()->getCurrentPointer()->setVisible ( false );
        MediaToolkit::getInstance()->getAudio()->stopMusic();

        while ( m_prerunning || m_playing )
        {
            if ( m_prerunning )
            {
                prerunTag ( MediaToolkit::getInstance() );
            }
            if ( m_playing )
            {
                playTag ( MediaToolkit::getInstance() );
            }
            if ( m_delayed )
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
        e.print ( "MoviePlayer::play" );
        throw;
    }
}

void MoviePlayer::prerunTag ( MediaToolkit* media )
{
    try
    {
        while ( ( m_prerunning ) && ( !m_delayed ) )
        {
            MovieTag *tag = (*m_movieTags)[m_prerunTag];
            switch ( tag->code )
            {
            case PREDRAW_SCREEN:
                m_screenSlot->getImage()->draw ( 0, 0 );
                break;
            case FADE_OUT:
                m_paletteSlot[m_currPalette]->getPalette()->fadeOut ( tag->data[0], tag->data[1], 64 << ( tag->data[2] & 0x0f ), 2 << tag->data[3] );
                media->getVideo()->clear();
                m_paletteActivated = true;
                break;
            case UPDATE:
                m_prerunning = false;
                m_playing = true;
                break;
            case COMMENT:
                break;
            case SLOT_IMAGE:
                m_currImage = tag->data[0];
                break;
            case SLOT_PALETTE:
                m_currPalette = tag->data[0];
                m_paletteActivated = false;
                break;
            case LOAD_SOUNDRESOURCE:
                break;
            case LOAD_SCREEN:
                if ( m_screenSlot )
                {
                    delete m_screenSlot;
                }
                tag->name[tag->name.length() - 1] = 'X';
                m_screenSlot = new ScreenResource;
                FileManager::getInstance()->load ( m_screenSlot, tag->name );
                m_screenSlot->getImage()->draw ( 0, 0 );
                break;
            case LOAD_IMAGE:
                if ( m_imageSlot[m_currImage] )
                {
                    delete m_imageSlot[m_currImage];
                }
                tag->name[tag->name.length() - 1] = 'X';
                m_imageSlot[m_currImage] = new ImageResource;
                FileManager::getInstance()->load ( m_imageSlot[m_currImage], tag->name );
                break;
            case LOAD_PALETTE:
                if ( m_paletteSlot[m_currPalette] )
                {
                    delete m_paletteSlot[m_currPalette];
                }
                m_paletteSlot[m_currPalette] = new PaletteResource;
                FileManager::getInstance()->load ( m_paletteSlot[m_currPalette], tag->name );
                m_paletteActivated = false;
                break;
            default:
                break;
            }
            m_prerunTag++;
            if ( m_prerunTag == m_movieTags->size() )
            {
                m_prerunning = false;
                m_playing = true;
            }
        }
    }
    catch ( Exception &e )
    {
        e.print ( "MoviePlayer::prerunTag" );
        throw;
    }
}

void MoviePlayer::playTag ( MediaToolkit* media )
{
    try
    {
        while ( ( m_playing ) && ( !m_delayed ) )
        {
            MovieTag *tag = ( *m_movieTags ) [m_currTag];
            switch ( tag->code )
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
                m_prerunning = true;
                m_playing = false;
                break;
            case DELAY:
                m_currDelay = tag->data[0] * 10;
                break;
            case DRAW_SCREEN:
                m_screenSlot->getImage()->draw ( 0, 0 );
                break;
            case FADE_IN:
                m_paletteSlot[m_currPalette]->getPalette()->fadeIn ( tag->data[0], tag->data[1], 64 << ( tag->data[2] & 0x0f ), 2 << tag->data[3] );
                m_paletteActivated = true;
                break;
            case SAVE_IMAGE0:
            case SAVE_IMAGE1:
                if ( m_savedImage != 0 )
                {
                    delete m_savedImage;
                }
                m_xSavedImage = tag->data[0];
                m_ySavedImage = tag->data[1];
                m_savedImage = new Image ( tag->data[2], tag->data[3] );
                m_savedImage->read ( m_xSavedImage, m_ySavedImage );
                m_savedImageDrawn = false;
                break;
            case CLEAR_WINDOW:
                media->getVideo()->clear(tag->data[0], tag->data[1], tag->data[2], tag->data[3]);
                break;
            case DRAW_IMAGE0:
            case DRAW_IMAGE1:
            case DRAW_IMAGE2:
            case DRAW_IMAGE3:
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
                if ( m_imageSlot[tag->data[3]] )
                {
                    m_imageSlot[tag->data[3]]->getImage ( tag->data[2] )->draw ( tag->data[0], tag->data[1], 0 );
                }
                break;
            case REDRAW_SCREEN:
                if ( ( m_backgroundImage != 0 ) && ( !m_backgroundImageDrawn ) )
                {
                    m_backgroundImage->draw ( 0, 0 );
                    m_backgroundImageDrawn = true;
                }
                if ( m_screenSlot )
                {
                    m_screenSlot->getImage()->draw ( tag->data[0], tag->data[1] );
                }
                break;
            case SELECT_SOUND:
            {
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( tag->data[0] );
                if ( it != m_soundMap.end() )
                {
                    if ( it->second >= 0 )
                    {
                        media->getAudio()->stopSound ( it->second );
                    }
                    m_soundMap.erase ( it );
                }
                m_soundMap.insert ( std::pair<unsigned int, int> ( tag->data[0], -1 ) );
            }
            break;
            case DESELECT_SOUND:
            {
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( tag->data[0] );
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
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( tag->data[0] );
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
                std::map<unsigned int, int>::iterator it = m_soundMap.find ( tag->data[0] );
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
            default:
                break;
            }
            m_currTag++;
            if ( m_currTag == m_movieTags->size() )
            {
                m_playing = false;
                if ( m_looped )
                {
                    m_prerunning = true;
                    m_prerunTag = 0;
                    m_currTag = 0;
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
                    m_prerunning = false;
                }
            }
        }
    }
    catch ( Exception &e )
    {
        e.print ( "MoviePlayer::playTag" );
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
        m_prerunning = false;
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
        m_prerunning = false;
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
