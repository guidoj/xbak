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

#include <sstream>

#include "animationresource.h"
#include "bookresource.h"
#include "chapter.h"
#include "exception.h"
#include "fontresource.h"
#include "filemanager.h"
#include "movieplayer.h"
#include "popupwidget.h"
#include "taggedimageresource.h"
#include "textwidget.h"

Chapter::Chapter ( const int n )
    : m_number ( n )
    , m_delayed ( false )
    , m_zone()
{
    MediaToolkit::getInstance()->addKeyboardListener ( this );
    MediaToolkit::getInstance()->addPointerButtonListener ( this );
    MediaToolkit::getInstance()->addTimerListener ( this );
    m_zone.load ( m_number );
}

Chapter::~Chapter()
{
    MediaToolkit::getInstance()->removeTimerListener ( this );
    MediaToolkit::getInstance()->removePointerButtonListener ( this );
    MediaToolkit::getInstance()->removeKeyboardListener ( this );
}

void Chapter::playIntro()
{
    try
    {
        AnimationResource anim;
        std::stringstream filenameStream;
        filenameStream << "CHAPTER" << m_number << ".ADS";
        FileManager::getInstance()->load ( &anim, filenameStream.str() );
        MovieResource ttm;
        FileManager::getInstance()->load ( &ttm, anim.getAnimationData ( 1 ).m_resource );
        MoviePlayer moviePlayer;
        moviePlayer.play ( &ttm.getMovieTags(), false );
        MediaToolkit::getInstance()->getVideo()->clear();
        MediaToolkit::getInstance()->getVideo()->refresh();
    }
    catch ( Exception &e )
    {
        e.print ( "Chapter::playIntro" );
    }
}

void Chapter::playScene ( const int scene )
{
    try
    {
        ScreenResource scr;
        FileManager::getInstance()->load ( &scr, "CFRAME.SCX" );
        scr.getImage()->draw ( 0, 0 );
        AnimationResource anim;
        std::stringstream filenameStream;
        filenameStream << "C" << m_number << scene << ".ADS";
        FileManager::getInstance()->load ( &anim, filenameStream.str() );
        MovieResource ttm;
        FileManager::getInstance()->load ( &ttm, anim.getAnimationData ( 1 ).m_resource );
        MoviePlayer moviePlayer;
        moviePlayer.play ( &ttm.getMovieTags(), false );
    }
    catch ( Exception &e )
    {
        e.print ( "Chapter::playIntro" );
    }
}

void Chapter::readBook ( const int scene )
{
    const std::string ROMAN_NUMBER[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV"};

    try
    {
        PaletteResource pal;
        FileManager::getInstance()->load ( &pal, "BOOK.PAL" );
        ScreenResource scr;
        FileManager::getInstance()->load ( &scr, "BOOK.SCX" );
        TaggedImageResource img;
        FileManager::getInstance()->load ( &img, "BOOK.BMX" );
        FontResource fnt;
        FileManager::getInstance()->load ( &fnt, "BOOK.FNT" );
        BookResource bok;
        std::stringstream filenameStream;
        filenameStream << "C" << m_number << scene << ".BOK";
        FileManager::getInstance()->load ( &bok, filenameStream.str() );
        Video *video = MediaToolkit::getInstance()->getVideo();
        video->setMode ( HIRES_LOCOL );

        Text txt;
        for ( unsigned int i = 0; i < bok.getSize(); i++ )
        {
            PageData pd = bok.getPage ( i );
            Image page ( scr.getImage() );
            if ( pd.number & 1 )
            {
                page.verticalFlip();
            }
            page.draw ( 0, 0 );

            for ( unsigned int j = 0; j < pd.decorations.size(); j++ )
            {
                if ( pd.decorations[j].id < img.getNumImages() )
                {
                    Image deco ( img.getImage ( pd.decorations[j].id ) );
                    if ( pd.decorations[j].flag & DECO_HORIZONTAL_FLIP )
                    {
                        deco.horizontalFlip();
                    }
                    if ( pd.decorations[j].flag & DECO_VERTICAL_FLIP )
                    {
                        deco.verticalFlip();
                    }
                    deco.draw ( pd.decorations[j].xpos, pd.decorations[j].ypos, 0 );
                }
            }

            int xoff = 0;
            for ( unsigned int j = 0; j < pd.firstLetters.size(); j++ )
            {
                if ( pd.firstLetters[j].id < img.getNumImages() )
                {
                    Image* letter = img.getImage ( pd.firstLetters[j].id );
                    letter->draw ( pd.firstLetters[j].xpos, pd.firstLetters[j].ypos, 0 );
                    xoff = letter->getWidth() - 49;
                }
            }

            Paragraph paragraph ( fnt.getFont() );
            paragraph.setAlignment ( HA_FILL, VA_TOP );
            paragraph.setIndent ( 30 );
            bool paragraphAdded = false;
            for ( unsigned int j = 0; j < pd.textBlocks.size() ; j++ )
            {
                if ( pd.textBlocks[j].txt.size() > 0 )
                {
                    TextBlock tb ( pd.textBlocks[j].txt, 0, NO_SHADOW, 0, 0, pd.textBlocks[j].italic );
                    if ( pd.textBlocks[j].paragraph )
                    {
                        paragraph.addTextBlock ( tb );
                    }
                }
                else
                {
                    if ( paragraph.getSize() > 0 )
                    {
                        txt.addParagraph ( paragraph );
                        paragraphAdded = true;
                        paragraph.clear();
                    }
                }
            }
            if ( paragraph.getSize() > 0 )
            {
                txt.addParagraph ( paragraph );
                paragraphAdded = true;
            }
            if ( paragraphAdded )
            {
                txt.generateLines ( pd.width - 20, xoff );
            }
            txt.drawPage ( pd.xpos + 10, pd.ypos + 4, pd.width - 20, pd.height - 4 );

            TextWidget pageNumberWidget ( Rectangle ( pd.xpos + 2, pd.ypos + pd.height + 11, pd.width - 4, fnt.getFont()->getHeight() ), fnt.getFont() );
            pageNumberWidget.setAlignment ( ( pd.number & 1 ) ? HA_RIGHT : HA_LEFT, VA_CENTER );
            pageNumberWidget.setText ( ROMAN_NUMBER[pd.number] );
            pageNumberWidget.draw();

            pal.getPalette()->fadeIn ( 0, PALETTE_COLORS, 64, 5 );
            MediaToolkit::getInstance()->getClock()->startTimer ( TMR_CHAPTER, 10000 );
            m_delayed = true;
            while ( m_delayed )
            {
                MediaToolkit::getInstance()->waitEvents();
            }
            pal.getPalette()->fadeOut ( 0, PALETTE_COLORS, 64, 5 );
        }
        video->setMode ( LORES_HICOL );
    }
    catch ( Exception &e )
    {
        e.print ( "Chapter::readBook" );
    }
}

void Chapter::showMap()
{
    try
    {
        PaletteResource pal;
        FileManager::getInstance()->load ( &pal, "FULLMAP.PAL" );
        ScreenResource scr;
        FileManager::getInstance()->load ( &scr, "FULLMAP.SCX" );
        scr.getImage()->draw ( 0, 0 );
        PopUpWidget popup ( Rectangle ( 13, 160, 159, 29 ) );
        popup.draw();
        pal.getPalette()->fadeIn ( 0, PALETTE_COLORS, 64, 5 );
        MediaToolkit::getInstance()->getClock()->startTimer ( TMR_CHAPTER, 4000 );
        m_delayed = true;
        while ( m_delayed )
        {
            MediaToolkit::getInstance()->waitEvents();
        }
        pal.getPalette()->fadeOut ( 0, PALETTE_COLORS, 64, 5 );
    }
    catch ( Exception &e )
    {
        e.print ( "Chapter::showMap" );
    }
}

int Chapter::get() const
{
    return m_number;
}

Zone& Chapter::getZone()
{
    return m_zone;
}

void Chapter::next()
{
    m_number++;
    m_zone.load ( m_number );
}

void Chapter::start ( const bool maponly )
{
    try
    {
        if ( !maponly )
        {
            playIntro();
            readBook ( 1 );
            playScene ( 1 );
        }
        showMap();
    }
    catch ( Exception &e )
    {
        e.print ( "Chapter::start" );
    }
}

void Chapter::keyPressed ( const KeyboardEvent &kbe )
{
    switch ( kbe.getKey() )
    {
    case KEY_ESCAPE:
    case KEY_RETURN:
    case KEY_SPACE:
        MediaToolkit::getInstance()->getClock()->stopTimer ( TMR_CHAPTER );
        m_delayed = false;
        break;
    default:
        break;
    }
}

void Chapter::keyReleased ( const KeyboardEvent &kbe )
{
    switch ( kbe.getKey() )
    {
    default:
        break;
    }
}

void Chapter::pointerButtonPressed ( const PointerButtonEvent &pbe )
{
    switch ( pbe.getButton() )
    {
    case PB_PRIMARY:
        MediaToolkit::getInstance()->getClock()->stopTimer ( TMR_CHAPTER );
        m_delayed = false;
        break;
    default:
        break;
    }
}

void Chapter::pointerButtonReleased ( const PointerButtonEvent &pbe )
{
    switch ( pbe.getButton() )
    {
    default:
        break;
    }
}

void Chapter::timerExpired ( const TimerEvent &te )
{
    if ( te.getId() == TMR_CHAPTER )
    {
        m_delayed = false;
    }
}
