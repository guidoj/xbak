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
private:
    int m_xPos;
    int m_yPos;

    Key getKey( int sc );
    void handleEvent ( SDL_Event *event );

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
