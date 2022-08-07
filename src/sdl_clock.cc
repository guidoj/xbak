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
#include "sdl_clock.h"

Uint32 SDL_Clock_TimerHandler(Uint32 ms, void *param)
{
    SDL_UserEvent userEvent;
    SDL_Event event;

    userEvent.type = SDL_USEREVENT;
    userEvent.code = ms;
    userEvent.data1 = param;
    userEvent.data2 = 0;
    event.type = SDL_USEREVENT;
    event.user = userEvent;
    SDL_PushEvent(&event);
    return 0;
}

SDL_Clock::SDL_Clock()
    : m_timers()
{}

SDL_Clock::~SDL_Clock()
{
    m_timers.clear();
}

unsigned long SDL_Clock::getTicks() const
{
    return SDL_GetTicks64();
}

void SDL_Clock::delay(int ms)
{
    if (ms > 0)
    {
        SDL_Delay(ms);
    }
}

void SDL_Clock::startTimer(unsigned long n, int ms)
{
    SDL_TimerID id = SDL_AddTimer(ms, SDL_Clock_TimerHandler, (void *)n);
    if (id == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    m_timers[n] = id;
}

void SDL_Clock::stopTimer(unsigned long n)
{
    std::map <const unsigned long, SDL_TimerID>::iterator it = m_timers.find(n);
    if (it != m_timers.end())
    {
        SDL_RemoveTimer(it->second);
        m_timers.erase(it);
    }
}

void SDL_Clock::cleanUpTimer(unsigned long n)
{
    std::map <const unsigned long, SDL_TimerID>::iterator it = m_timers.find(n);
    if (it != m_timers.end())
    {
        m_timers.erase(it);
    }
}
