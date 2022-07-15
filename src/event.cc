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

#include "event.h"

KeyboardEvent::KeyboardEvent(const Key k)
    : m_key(k)
{}

KeyboardEvent::~KeyboardEvent()
{}

Key
KeyboardEvent::getKey() const
{
    return m_key;
}

PointerButtonEvent::PointerButtonEvent(const PointerButton b, const int x, const int y)
    : m_button(b)
    , m_xpos(x)
    , m_ypos(y)
{}

PointerButtonEvent::~PointerButtonEvent()
{}

PointerButton
PointerButtonEvent::getButton() const
{
    return m_button;
}

int
PointerButtonEvent::getXPos() const
{
    return m_xpos;
}

int
PointerButtonEvent::getYPos() const
{
    return m_ypos;
}

PointerMotionEvent::PointerMotionEvent(const int x, const int y)
    : m_xpos(x)
    , m_ypos(y)
{}

PointerMotionEvent::~PointerMotionEvent()
{}

int
PointerMotionEvent::getXPos() const
{
    return m_xpos;
}

int
PointerMotionEvent::getYPos() const
{
    return m_ypos;
}

TimerEvent::TimerEvent(const unsigned long n)
    : m_id(n)
{}

TimerEvent::~TimerEvent()
{}

unsigned long
TimerEvent::getId() const
{
    return m_id;
}

LoopEvent::LoopEvent(const int t)
    : m_ticks(t)
{}

LoopEvent::~LoopEvent()
{}

int
LoopEvent::getTicks() const
{
    return m_ticks;
}

ActionEvent::ActionEvent(const int a, const int x, const int y)
    : m_action(a)
    , m_xpos(x)
    , m_ypos(y)
{}

ActionEvent::~ActionEvent()
{}

int
ActionEvent::getAction() const
{
    return m_action;
}

int
ActionEvent::getXPos() const
{
    return m_xpos;
}

int
ActionEvent::getYPos() const
{
    return m_ypos;
}

DragEvent::DragEvent(const bool t, const int x, const int y)
    : m_toggle(t)
    , m_xpos(x)
    , m_ypos(y)
{}

DragEvent::~DragEvent()
{}

bool
DragEvent::getToggle() const
{
    return m_toggle;
}

int
DragEvent::getXPos() const
{
    return m_xpos;
}

int
DragEvent::getYPos() const
{
    return m_ypos;
}
