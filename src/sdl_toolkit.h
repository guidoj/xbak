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

#ifndef SDL_TOOLKIT_H
#define SDL_TOOLKIT_H

#include <SDL.h>

#include "mediatoolkit.h"

class SDL_Toolkit
    : public MediaToolkit
{
    enum JoystickState { JS_CENTER,
                         JS_UP,
                         JS_UP_LEFT,
                         JS_LEFT,
                         JS_DOWN_LEFT,
                         JS_DOWN,
                         JS_DOWN_RIGHT,
                         JS_RIGHT,
                         JS_UP_RIGHT
                       };

private:
    int m_xPos;
    int m_yPos;
    int m_xMove;
    int m_yMove;
    enum JoystickState m_jsState;
    SDL_Joystick *m_joystick;
    void handleEvent ( SDL_Event *event );
    void updatePointer();
public:
    SDL_Toolkit();
    ~SDL_Toolkit();
    void pollEvents();
    void pollEventLoop();
    void waitEvents();
    void waitEventLoop();
    void clearEvents();
    void getPointerPosition ( int *x, int *y );
    void setPointerPosition ( int x, int y );
};

#endif

