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

#ifndef SDL_CLOCK_H
#define SDL_CLOCK_H

#include <SDL.h>
#include <map>

#include "clock.h"

class SDL_Clock: public Clock
{
private:
    std::map <const unsigned long, SDL_TimerID> m_timers;
public:
    SDL_Clock();
    virtual ~SDL_Clock();
    unsigned long getTicks() const;
    void delay ( int ms );
    void startTimer ( unsigned long n, int ms );
    void stopTimer ( unsigned long n );
    void cleanUpTimer ( unsigned long n );
};

#endif

