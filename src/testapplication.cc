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
#include "filemanager.h"
#include "movieplayer.h"
#include "pointermanager.h"
#include "sdl_toolkit.h"
#include "testapplication.h"
#include "text.h"
#include "textwidget.h"

TestApplication* TestApplication::m_instance = 0;

TestApplication::TestApplication()
    : m_pal()
    , m_fnt()
    , m_img()
    , m_scr()
    , m_ttm()
    , m_wld()
{
    MediaToolkit *media = MediaToolkit::getInstance();
    media->getVideo()->createWindow();
    media->getVideo()->setMode ( LORES_HICOL );
    PointerManager::getInstance()->addPointer ( "POINTER.BMX" );
    media->addKeyboardListener ( this );
    media->addTimerListener ( this );
}

TestApplication::~TestApplication()
{
    MediaToolkit *media = MediaToolkit::getInstance();
    media->removeKeyboardListener ( this );
    media->removeTimerListener ( this );
    PointerManager::cleanUp();
    MediaToolkit::cleanUp();
    SoundResource::cleanUp();
    FileManager::cleanUp();
}

TestApplication* TestApplication::getInstance()
{
    if ( !m_instance )
    {
        m_instance = new TestApplication();
    }
    return m_instance;
}

void TestApplication::cleanUp()
{
    if ( m_instance )
    {
        delete m_instance;
        m_instance = 0;
    }
}

void TestApplication::activatePalette()
{
    try
    {
        m_pal.getPalette()->fill();
        m_pal.getPalette()->activate ( 0, 256 );
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::activatePalette" );
    }
}

void TestApplication::activatePalette ( const std::string& name )
{
    try
    {
        FileManager::getInstance()->load ( &m_pal, name );
        m_pal.getPalette()->activate ( 0, 256 );
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::activatePalette" );
    }
}

void TestApplication::showImage ( const std::string& name )
{
    try
    {
        MediaToolkit *media = MediaToolkit::getInstance();
        FileManager::getInstance()->load ( &m_img, name );
        for ( unsigned int i = 0; i < m_img.getNumImages(); i++ )
        {
            media->getVideo()->clear();
            m_img.getImage ( i )->draw ( 0, 0 );
            media->getVideo()->refresh();
            media->getClock()->startTimer ( TMR_TEST_APP, 5000 );
            media->waitEventLoop();
            media->getClock()->stopTimer ( TMR_TEST_APP );
        }
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::showImage" );
    }
}

void TestApplication::showTaggedImage ( const std::string& name )
{
    try
    {
        MediaToolkit *media = MediaToolkit::getInstance();
        FileManager::getInstance()->load ( &m_timg, name );
        for ( unsigned int i = 0; i < m_timg.getNumImages(); i++ )
        {
            media->getVideo()->clear();
            m_timg.getImage ( i )->draw ( 0, 0 );
            media->getVideo()->refresh();
            media->getClock()->startTimer ( TMR_TEST_APP, 5000 );
            media->waitEventLoop();
            media->getClock()->stopTimer ( TMR_TEST_APP );
        }
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::showImage" );
    }
}

void TestApplication::showScreen ( const std::string& name )
{
    try
    {
        MediaToolkit *media = MediaToolkit::getInstance();
        FileManager::getInstance()->load ( &m_scr, name );
        if ( m_scr.getImage()->isHighResLowCol() )
        {
            media->getVideo()->setMode ( HIRES_LOCOL );
        }
        media->getVideo()->clear();
        m_scr.getImage()->draw ( 0, 0 );
        media->getVideo()->refresh();
        media->getClock()->startTimer ( TMR_TEST_APP, 10000 );
        media->waitEventLoop();
        media->getClock()->stopTimer ( TMR_TEST_APP );
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::showScreen" );
    }
}

void TestApplication::drawFont ( const std::string& name )
{
    try
    {
        MediaToolkit *media = MediaToolkit::getInstance();
        FileManager::getInstance()->load ( &m_fnt, name );
        media->getVideo()->clear();
        Text txt;
        Paragraph pg1 ( m_fnt.getFont() );
        TextBlock tb1a ( "The quick brown fox jumped over the lazy dog.", 15, NO_SHADOW, 0, 0, false );
        pg1.addTextBlock ( tb1a );
        TextBlock tb1b ( "The quick brown fox jumped over the lazy dog.", 15, NO_SHADOW, 0, 0, true );
        pg1.addTextBlock ( tb1b );
        txt.addParagraph ( pg1 );
        Paragraph pg2 ( m_fnt.getFont() );
        pg2.setIndent( 20 );
        TextBlock tb2 ( "This is just a rather long text to test wrapping lines at the end of the text box. Just some more text to be sure that the text will be wrapped around at the edges.", 15, NO_SHADOW, 0, 0, false );
        pg2.addTextBlock ( tb2 );
        txt.addParagraph ( pg2 );
        txt.generateLines ( 280, 0 );
        txt.drawPage ( 10, 10, 280, 180 );
        media->getVideo()->refresh();
        media->getClock()->startTimer ( TMR_TEST_APP, 5000 );
        media->waitEventLoop();
        media->getClock()->stopTimer ( TMR_TEST_APP );
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::drawFont" );
    }
}

void TestApplication::playMovie ( const std::string& name )
{
    try
    {
        FileManager::getInstance()->load ( &m_ttm, name );
        MoviePlayer moviePlayer;
        moviePlayer.play ( &m_ttm.getMovieChunks(), false );
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::playMovie" );
    }
}

void TestApplication::playSound ( const unsigned int index )
{
    try
    {
        MediaToolkit *media = MediaToolkit::getInstance();
        SoundData data = SoundResource::getInstance()->getSoundData ( index );
        unsigned int channel = -1;
        if (data.type == SND_TYPE_MIDI)
        {
            channel = media->getAudio()->playMusic ( data.sounds[0]->getSamples() );
        }
        else
        {
            channel = media->getAudio()->playSound ( data.sounds[0]->getSamples() );
        }
        media->getClock()->startTimer ( TMR_TEST_APP, ( index < 1000 ? 5000 : 30000 ) );
        media->waitEventLoop();
        media->getClock()->stopTimer ( TMR_TEST_APP );
        media->getAudio()->stopSound ( channel );
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::playSound" );
    }
}

void TestApplication::walkWorld ( const std::string& zone, const std::string& tile )
{
    try
    {
        MediaToolkit *media = MediaToolkit::getInstance();
        FileManager::getInstance()->load ( &m_img, "Z" + zone + "SLOT0.BMX" );
        FileManager::getInstance()->load ( &m_wld, "T" + zone + tile + ".WLD" );
        m_img.getImage ( 0 )->draw ( 0, 0 );
        Image *image = new Image ( m_img.getImage ( 0 )->getWidth() / 2, m_img.getImage ( 0 )->getHeight() / 2, m_img.getImage ( 0 ) );
        image->draw ( 160, 0 );
        delete image;
        media->getVideo()->drawLine ( 10, 10, 200, 150, 1 );
        media->getVideo()->drawLine ( 240, 20, 20, 160, 2 );
        media->getVideo()->drawLine ( 300, 180, 190, 30, 3 );
        media->getVideo()->drawLine ( 40, 170, 250, 40, 4 );
        int x0[3] = {100, 150, 120};
        int y0[3] = {60, 50, 120};
        media->getVideo()->drawPolygon ( x0, y0, 3, 5 );
        int x1[6] = {100, 100, 160, 280, 280, 200};
        int y1[6] = {90, 150, 190, 90, 150, 90};
        media->getVideo()->fillPolygon ( x1, y1, 6, 6 );
        int x2[3] = {-40, 10, -10};
        int y2[3] = {150, 180, 120};
        media->getVideo()->fillPolygon ( x2, y2, 3, 7 );
        media->getVideo()->refresh();
        media->getClock()->startTimer ( TMR_TEST_APP, 5000 );
        media->waitEventLoop();
        media->getClock()->stopTimer ( TMR_TEST_APP );
    }
    catch ( Exception &e )
    {
        e.print ( "TestApplication::walkWorld" );
    }
}

void TestApplication::keyPressed ( const KeyboardEvent &kbe )
{
    switch ( kbe.getKey() )
    {
    case KEY_ESCAPE:
    case KEY_RETURN:
    case KEY_SPACE:
        MediaToolkit::getInstance()->terminateEventLoop();
        break;
    case KEY_F11:
        MediaToolkit::getInstance()->getVideo()->saveScreenShot ( "screenshot.bmp" );
        break;
    default:
        break;
    }
}

void TestApplication::keyReleased ( const KeyboardEvent &kbe )
{
    switch ( kbe.getKey() )
    {
    default:
        break;
    }
}

void TestApplication::timerExpired ( const TimerEvent &te )
{
    if ( te.getId() == TMR_TEST_APP )
    {
        MediaToolkit::getInstance()->terminateEventLoop();
    }
}
