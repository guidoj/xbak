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
#include "sdl_audio.h"
#include "sdl_clock.h"
#include "sdl_toolkit.h"
#include "sdl_video.h"

SDL_Toolkit::SDL_Toolkit()
    : MediaToolkit()
    , m_xPos(0)
    , m_yPos(0)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    m_audio = new SDL_Audio();
    m_clock = new SDL_Clock();
    m_video = new SDL_Video();
}

SDL_Toolkit::~SDL_Toolkit()
{
    m_video->grabInput(false);
    delete m_audio;
    delete m_clock;
    delete m_video;
    SDL_Quit();
}

Key
SDL_Toolkit::getKey ( int sc )
{
    switch ( sc )
    {
    case SDL_SCANCODE_TAB:
        return KEY_TAB;
    case SDL_SCANCODE_RETURN:
        return KEY_RETURN;
    case SDL_SCANCODE_ESCAPE:
        return KEY_ESCAPE;
    case SDL_SCANCODE_SPACE:
        return KEY_SPACE;
    case SDL_SCANCODE_LEFT:
        return KEY_LEFT;
    case SDL_SCANCODE_RIGHT:
        return KEY_RIGHT;
    case SDL_SCANCODE_UP:
        return KEY_UP;
    case SDL_SCANCODE_DOWN:
        return KEY_DOWN;
    case SDL_SCANCODE_F11:
        return KEY_F11;
    case SDL_SCANCODE_F12:
        return KEY_F12;
    default:
        return KEY_UNDEFINED;
    }
}

void
SDL_Toolkit::handleEvent(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
    {
        KeyboardEvent kbe(getKey(event->key.keysym.scancode));
        if (kbe.getKey() != KEY_UNDEFINED)
        {
            for (std::list<KeyboardEventListener *>::iterator it = m_keyboardListeners.begin(); it != m_keyboardListeners.end(); ++it)
            {
                (*it)->keyPressed(kbe);
            }
        }
    }
    break;
    case SDL_KEYUP:
    {
        KeyboardEvent kbe(getKey(event->key.keysym.scancode));
        if (kbe.getKey() != KEY_UNDEFINED)
        {
            for (std::list<KeyboardEventListener *>::iterator it = m_keyboardListeners.begin(); it != m_keyboardListeners.end(); ++it)
            {
                (*it)->keyReleased(kbe);
            }
        }
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
    {
        PointerButton pb;
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            pb = PB_PRIMARY;
            break;
        case SDL_BUTTON_MIDDLE:
            pb = PB_TERTIARY;
            break;
        case SDL_BUTTON_RIGHT:
            pb = PB_SECONDARY;
            break;
        default:
            return;
        }
        m_xPos = event->button.x;
        m_yPos = event->button.y;
        PointerButtonEvent pbe(pb, m_xPos, m_yPos);
        for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
        {
            (*it)->pointerButtonPressed(pbe);
        }
    }
    break;
    case SDL_MOUSEBUTTONUP:
    {
        PointerButton pb;
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
            pb = PB_PRIMARY;
            break;
        case SDL_BUTTON_MIDDLE:
            pb = PB_TERTIARY;
            break;
        case SDL_BUTTON_RIGHT:
            pb = PB_SECONDARY;
            break;
        default:
            return;
        }
        m_xPos = event->button.x;
        m_yPos = event->button.y;
        PointerButtonEvent pbe(pb, m_xPos, m_yPos);
        for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
        {
            (*it)->pointerButtonReleased(pbe);
        }
    }
    break;
    case SDL_MOUSEMOTION:
    {
        m_xPos = event->button.x;
        m_yPos = event->button.y;
        PointerMotionEvent pme(m_xPos, m_yPos);
        for (std::list<PointerMotionEventListener *>::iterator it = m_pointerMotionListeners.begin(); it != m_pointerMotionListeners.end(); ++it)
        {
            (*it)->pointerMoved(pme);
        }
    }
    break;
    case SDL_USEREVENT:
    {
        // timer event
        m_clock->cleanUpTimer((unsigned long)event->user.data1);
        TimerEvent te((unsigned long)event->user.data1);
        for (std::list<TimerEventListener *>::iterator it = m_timerListeners.begin(); it != m_timerListeners.end(); ++it)
        {
            (*it)->timerExpired(te);
        }
    }
    break;
    default:
        break;
    }
}

void
SDL_Toolkit::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        handleEvent(&event);
    }
}

void
SDL_Toolkit::pollEventLoop()
{
    unsigned long currentTicks;
    unsigned long previousTicks = SDL_GetTicks64();

    m_eventLoopRunning = true;
    while (m_eventLoopRunning)
    {
        pollEvents();
        currentTicks = SDL_GetTicks64();
        LoopEvent le(currentTicks - previousTicks);
        for (std::list<LoopEventListener *>::iterator it = m_loopListeners.begin(); it != m_loopListeners.end(); ++it)
        {
            (*it)->loopComplete(le);
        }
        previousTicks = currentTicks;
    }
}

void
SDL_Toolkit::waitEvents()
{
    SDL_Event event;
    if (SDL_WaitEvent(&event))
    {
        handleEvent(&event);
    }
}

void
SDL_Toolkit::waitEventLoop()
{
    unsigned long currentTicks;
    unsigned long previousTicks = SDL_GetTicks64();

    m_eventLoopRunning = true;
    while (m_eventLoopRunning)
    {
        waitEvents();
        currentTicks = SDL_GetTicks64();
        LoopEvent le(currentTicks - previousTicks);
        for (std::list<LoopEventListener *>::iterator it = m_loopListeners.begin(); it != m_loopListeners.end(); ++it)
        {
            (*it)->loopComplete(le);
        }
        previousTicks = currentTicks;
    }
}

void
SDL_Toolkit::clearEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // nothing
    }
}

void
SDL_Toolkit::getPointerPosition(int *x, int *y)
{
    SDL_GetMouseState(x, y);
}

void
SDL_Toolkit::setPointerPosition(int x, int y)
{
    SDL_WarpMouseInWindow(0, x, y);
}
