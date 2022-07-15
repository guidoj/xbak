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

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "event.h"

class KeyboardEventListener
{
public:
    KeyboardEventListener()
    {};
    virtual ~KeyboardEventListener()
    {};
    virtual void keyPressed ( const KeyboardEvent &kbe ) = 0;
    virtual void keyReleased ( const KeyboardEvent &kbe ) = 0;
};

class PointerButtonEventListener
{
public:
    PointerButtonEventListener()
    {};
    virtual ~PointerButtonEventListener()
    {};
    virtual void pointerButtonPressed ( const PointerButtonEvent &pbe ) = 0;
    virtual void pointerButtonReleased ( const PointerButtonEvent &pbe ) = 0;
};

class PointerMotionEventListener
{
public:
    PointerMotionEventListener()
    {};
    virtual ~PointerMotionEventListener()
    {};
    virtual void pointerMoved ( const PointerMotionEvent &mme ) = 0;
};

class TimerEventListener
{
public:
    TimerEventListener()
    {};
    virtual ~TimerEventListener()
    {};
    virtual void timerExpired ( const TimerEvent &te ) = 0;
};

class LoopEventListener
{
public:
    LoopEventListener()
    {};
    virtual ~LoopEventListener()
    {};
    virtual void loopComplete ( const LoopEvent &le ) = 0;
};

class ActionEventListener
{
public:
    ActionEventListener()
    {};
    virtual ~ActionEventListener()
    {};
    virtual void actionPerformed ( const ActionEvent &ae ) = 0;
};

class DragEventListener
{
public:
    DragEventListener()
    {};
    virtual ~DragEventListener()
    {};
    virtual void pointerDragged ( const DragEvent &de ) = 0;
};

#endif
