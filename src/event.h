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

#ifndef EVENT_H
#define EVENT_H

typedef enum
{
    /**/
    KEY_UNDEFINED,

    /* Regular keys */
    KEY_TAB,
    KEY_RETURN,
    KEY_ESCAPE,
    KEY_SPACE,

    /* Arrows + Home/End pad */
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,

    /* Function keys */
    KEY_F11,
    KEY_F12
} Key;

/* Timer ID's */
const unsigned long TMR_TEST_APP     = 1;
const unsigned long TMR_GAME_APP     = 2;
const unsigned long TMR_CHAPTER      = 3;
const unsigned long TMR_MOVIE_PLAYER = 4;
const unsigned long TMR_PALETTE      = 5;
const unsigned long TMR_MOVING       = 6;
const unsigned long TMR_TURNING      = 7;


typedef enum
{
    PB_PRIMARY,
    PB_SECONDARY,
    PB_TERTIARY
}
PointerButton;


class KeyboardEvent
{
private:
    Key m_key;
public:
    KeyboardEvent ( const Key k );
    virtual ~KeyboardEvent();
    Key getKey() const;
};

class PointerButtonEvent
{
private:
    PointerButton m_button;
    int m_xpos;
    int m_ypos;
public:
    PointerButtonEvent ( const PointerButton b, const int x, const int y );
    virtual ~PointerButtonEvent();
    PointerButton getButton() const;
    int getXPos() const;
    int getYPos() const;
};

class PointerMotionEvent
{
private:
    int m_xpos;
    int m_ypos;
public:
    PointerMotionEvent ( const int x, const int y );
    virtual ~PointerMotionEvent();
    int getXPos() const;
    int getYPos() const;
};

class TimerEvent
{
private:
    unsigned long m_id;
public:
    TimerEvent ( const unsigned long n );
    virtual ~TimerEvent();
    unsigned long getId() const;
};

class LoopEvent
{
private:
    unsigned long m_ticks;
public:
    LoopEvent ( const unsigned long t );
    virtual ~LoopEvent();
    unsigned long getTicks() const;
};

class ActionEvent
{
private:
    int m_action;
    int m_xpos;
    int m_ypos;
public:
    ActionEvent ( const int a, const int x, const int y );
    virtual ~ActionEvent();
    int getAction() const;
    int getXPos() const;
    int getYPos() const;
};

class DragEvent
{
private:
    bool m_toggle;
    int m_xpos;
    int m_ypos;
public:
    DragEvent ( const bool t, const int x, const int y );
    virtual ~DragEvent();
    bool getToggle() const;
    int getXPos() const;
    int getYPos() const;
};

#endif
