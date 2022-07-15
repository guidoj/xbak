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

#ifndef CHAPTER_H
#define CHAPTER_H

#include "eventlistener.h"
#include "zone.h"

class Chapter
    : public KeyboardEventListener
    , public PointerButtonEventListener
    , public TimerEventListener
{
private:
    int m_number;
    bool m_delayed;
    Zone m_zone;
    void playIntro();
    void playScene ( const int scene );
    void readBook ( const int scene );
    void showMap();
public:
    Chapter ( const int n );
    virtual ~Chapter();
    int get() const;
    Zone& getZone();
    void next();
    void start ( const bool maponly = false );
    void keyPressed ( const KeyboardEvent &kbe );
    void keyReleased ( const KeyboardEvent &kbe );
    void pointerButtonPressed ( const PointerButtonEvent &pbe );
    void pointerButtonReleased ( const PointerButtonEvent &pbe );
    void timerExpired ( const TimerEvent &te );
};

#endif
