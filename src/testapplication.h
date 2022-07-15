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

#ifndef TEST_APPLICATION_H
#define TEST_APPLICATION_H

#include "imageresource.h"
#include "fontresource.h"
#include "movieresource.h"
#include "paletteresource.h"
#include "screenresource.h"
#include "soundresource.h"
#include "taggedimageresource.h"
#include "tileworldresource.h"

class TestApplication
    : public KeyboardEventListener
    , public TimerEventListener
{
private:
    PaletteResource m_pal;
    FontResource m_fnt;
    ImageResource m_img;
    ScreenResource m_scr;
    MovieResource m_ttm;
    TaggedImageResource m_timg;
    TileWorldResource m_wld;
    SoundResource* m_snd;
    static TestApplication *m_instance;
protected:
    TestApplication();
public:
    ~TestApplication();
    static TestApplication* getInstance();
    static void cleanUp();
    void activatePalette();
    void activatePalette ( const std::string& name );
    void showImage ( const std::string& name );
    void showTaggedImage ( const std::string& name );
    void showScreen ( const std::string& name );
    void drawFont ( const std::string& name );
    void PlayMovie ( const std::string& name );
    void playSound ( const unsigned int index );
    void walkWorld ( const std::string& zone, const std::string& tile );
    void keyPressed ( const KeyboardEvent &kbe );
    void keyReleased ( const KeyboardEvent &kbe );
    void timerExpired ( const TimerEvent &te );
};

#endif
