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

#define GP2X_BUTTON_UP        (0)
#define GP2X_BUTTON_UPLEFT    (1)
#define GP2X_BUTTON_LEFT      (2)
#define GP2X_BUTTON_DOWNLEFT  (3)
#define GP2X_BUTTON_DOWN      (4)
#define GP2X_BUTTON_DOWNRIGHT (5)
#define GP2X_BUTTON_RIGHT     (6)
#define GP2X_BUTTON_UPRIGHT   (7)
#define GP2X_BUTTON_START     (8)
#define GP2X_BUTTON_SELECT    (9)
#define GP2X_BUTTON_R         (10)
#define GP2X_BUTTON_L         (11)
#define GP2X_BUTTON_A         (12)
#define GP2X_BUTTON_B         (13)
#define GP2X_BUTTON_Y         (14)
#define GP2X_BUTTON_X         (15)
#define GP2X_BUTTON_VOLUP     (16)
#define GP2X_BUTTON_VOLDOWN   (17)
#define GP2X_BUTTON_CLICK     (18)

#define GP2X_AXIS_FACTOR (20000)
#define GP2X_SPEED       (3)

// for now assume GP2X mapping ...
const int JOYSTICK_BUTTON_UP        = GP2X_BUTTON_UP;
const int JOYSTICK_BUTTON_UPLEFT    = GP2X_BUTTON_UPLEFT;
const int JOYSTICK_BUTTON_LEFT      = GP2X_BUTTON_LEFT;
const int JOYSTICK_BUTTON_DOWNLEFT  = GP2X_BUTTON_DOWNLEFT;
const int JOYSTICK_BUTTON_DOWN      = GP2X_BUTTON_DOWN;
const int JOYSTICK_BUTTON_DOWNRIGHT = GP2X_BUTTON_DOWNRIGHT;
const int JOYSTICK_BUTTON_RIGHT     = GP2X_BUTTON_RIGHT;
const int JOYSTICK_BUTTON_UPRIGHT   = GP2X_BUTTON_UPRIGHT;
const int JOYSTICK_BUTTON_PRIMARY   = GP2X_BUTTON_R;
const int JOYSTICK_BUTTON_SECONDARY = GP2X_BUTTON_L;
const int JOYSTICK_BUTTON_TERTIARY  = GP2X_BUTTON_CLICK;
const int JOYSTICK_AXIS_FACTOR      = GP2X_AXIS_FACTOR;
const int JOYSTICK_SPEED            = GP2X_SPEED;

SDL_Toolkit::SDL_Toolkit()
    : MediaToolkit()
    , m_xPos(0)
    , m_yPos(0)
    , m_xMove(0)
    , m_yMove(0)
    , m_joystick(0)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    m_audio = new SDL_Audio();
    m_clock = new SDL_Clock();
    m_video = new SDL_Video();

    if (SDL_NumJoysticks() > 0)
    {
        m_joystick = SDL_JoystickOpen(0);
        if (!m_joystick)
        {
            throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
        }
    }

}

SDL_Toolkit::~SDL_Toolkit()
{
    SDL_WM_GrabInput(SDL_GRAB_OFF);
    if (m_joystick)
    {
        SDL_JoystickClose(m_joystick);
    }
    delete m_audio;
    delete m_clock;
    delete m_video;
    SDL_Quit();
}

void
SDL_Toolkit::handleEvent(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
    {
        KeyboardEvent kbe((Key)event->key.keysym.sym);
        for (std::list<KeyboardEventListener *>::iterator it = m_keyboardListeners.begin(); it != m_keyboardListeners.end(); ++it)
        {
            (*it)->keyPressed(kbe);
        }
    }
    break;
    case SDL_KEYUP:
    {
        KeyboardEvent kbe((Key)event->key.keysym.sym);
        for (std::list<KeyboardEventListener *>::iterator it = m_keyboardListeners.begin(); it != m_keyboardListeners.end(); ++it)
        {
            (*it)->keyReleased(kbe);
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
        m_xPos = event->button.x / m_video->getScaling();
        m_yPos = event->button.y / m_video->getScaling();
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
        m_xPos = event->button.x / m_video->getScaling();
        m_yPos = event->button.y / m_video->getScaling();
        PointerButtonEvent pbe(pb, m_xPos, m_yPos);
        for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
        {
            (*it)->pointerButtonReleased(pbe);
        }
    }
    break;
    case SDL_MOUSEMOTION:
    {
        m_xPos = event->button.x / m_video->getScaling();
        m_yPos = event->button.y / m_video->getScaling();
        PointerMotionEvent pme(m_xPos, m_yPos);
        for (std::list<PointerMotionEventListener *>::iterator it = m_pointerMotionListeners.begin(); it != m_pointerMotionListeners.end(); ++it)
        {
            (*it)->pointerMoved(pme);
        }
    }
    break;
    case SDL_JOYAXISMOTION:
        if (event->jaxis.which == 0)
        {
            if (event->jaxis.axis == 0)
            {
                m_xMove = event->jaxis.value / JOYSTICK_AXIS_FACTOR;
            }
            else if (event->jaxis.axis == 1)
            {
                m_yMove = event->jaxis.value / JOYSTICK_AXIS_FACTOR;
            }
        }
        break;
    case SDL_JOYBUTTONDOWN:
        if (event->jbutton.which == 0)
        {
            switch (event->jbutton.button)
            {
            case JOYSTICK_BUTTON_UP:
                m_jsState = JS_UP;
                m_yMove = -1;
                break;
            case JOYSTICK_BUTTON_UPLEFT:
                m_jsState = JS_UP_LEFT;
                m_xMove = -1;
                m_yMove = -1;
                break;
            case JOYSTICK_BUTTON_LEFT:
                m_jsState = JS_LEFT;
                m_xMove = -1;
                break;
            case JOYSTICK_BUTTON_DOWNLEFT:
                m_jsState = JS_DOWN_LEFT;
                m_xMove = -1;
                m_yMove = 1;
                break;
            case JOYSTICK_BUTTON_DOWN:
                m_jsState = JS_DOWN;
                m_yMove = 1;
                break;
            case JOYSTICK_BUTTON_DOWNRIGHT:
                m_jsState = JS_DOWN_RIGHT;
                m_xMove = 1;
                m_yMove = 1;
                break;
            case JOYSTICK_BUTTON_RIGHT:
                m_jsState = JS_RIGHT;
                m_xMove = 1;
                break;
            case JOYSTICK_BUTTON_UPRIGHT:
                m_jsState = JS_UP_RIGHT;
                m_xMove = 1;
                m_yMove = -1;
                break;
            case JOYSTICK_BUTTON_PRIMARY:
            {
                PointerButtonEvent pbe(PB_PRIMARY, m_xPos, m_yPos);
                for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
                {
                    (*it)->pointerButtonPressed(pbe);
                }
            }
            break;
            case JOYSTICK_BUTTON_SECONDARY:
            {
                PointerButtonEvent pbe(PB_SECONDARY, m_xPos, m_yPos);
                for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
                {
                    (*it)->pointerButtonPressed(pbe);
                }
            }
            break;
            case JOYSTICK_BUTTON_TERTIARY:
            {
                PointerButtonEvent pbe(PB_TERTIARY, m_xPos, m_yPos);
                for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
                {
                    (*it)->pointerButtonPressed(pbe);
                }
            }
            break;
            default:
                break;
            }
        }
        break;
    case SDL_JOYBUTTONUP:
        if (event->jbutton.which == 0)
        {
            switch (event->jbutton.button)
            {
            case JOYSTICK_BUTTON_UP:
                if (m_jsState == JS_UP)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_UPLEFT:
                if (m_jsState == JS_UP_LEFT)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_LEFT:
                if (m_jsState == JS_LEFT)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_DOWNLEFT:
                if (m_jsState == JS_DOWN_LEFT)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_DOWN:
                if (m_jsState == JS_DOWN)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_DOWNRIGHT:
                if (m_jsState == JS_DOWN_RIGHT)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_RIGHT:
                if (m_jsState == JS_RIGHT)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_UPRIGHT:
                if (m_jsState == JS_UP_RIGHT)
                {
                    m_jsState = JS_CENTER;
                    m_xMove = 0;
                    m_yMove = 0;
                }
                break;
            case JOYSTICK_BUTTON_PRIMARY:
            {
                PointerButtonEvent pbe(PB_PRIMARY, m_xPos, m_yPos);
                for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
                {
                    (*it)->pointerButtonReleased(pbe);
                }
            }
            break;
            case JOYSTICK_BUTTON_SECONDARY:
            {
                PointerButtonEvent pbe(PB_SECONDARY, m_xPos, m_yPos);
                for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
                {
                    (*it)->pointerButtonReleased(pbe);
                }
            }
            break;
            case JOYSTICK_BUTTON_TERTIARY:
            {
                PointerButtonEvent pbe(PB_TERTIARY, m_xPos, m_yPos);
                for (std::list<PointerButtonEventListener *>::iterator it = m_pointerButtonListeners.begin(); it != m_pointerButtonListeners.end(); ++it)
                {
                    (*it)->pointerButtonReleased(pbe);
                }
            }
            break;
            default:
                break;
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
SDL_Toolkit::updatePointer()
{
    if (m_xMove)
    {
        m_xPos = m_xPos + m_xMove * JOYSTICK_SPEED;
        if (m_xPos < 0)
        {
            m_xPos = 0;
        }
        else if (m_xPos > m_video->getWidth())
        {
            m_xPos = m_video->getWidth();
        }
    }
    if (m_yMove)
    {
        m_yPos = m_yPos + m_yMove * JOYSTICK_SPEED;
        if (m_yPos < 0)
        {
            m_yPos = 0;
        }
        else if (m_yPos > m_video->getHeight())
        {
            m_yPos = m_video->getHeight();
        }
    }
    if (m_xMove || m_yMove)
    {
        PointerMotionEvent pme(m_xPos, m_yPos);
        for (std::list<PointerMotionEventListener *>::iterator it = m_pointerMotionListeners.begin(); it != m_pointerMotionListeners.end(); ++it)
        {
            (*it)->pointerMoved(pme);
        }
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
    updatePointer();
}

void
SDL_Toolkit::pollEventLoop()
{
    int currentTicks;
    int previousTicks = SDL_GetTicks();

    m_eventLoopRunning = true;
    while (m_eventLoopRunning)
    {
        pollEvents();
        currentTicks = SDL_GetTicks();
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
    updatePointer();
}

void
SDL_Toolkit::waitEventLoop()
{
    int currentTicks;
    int previousTicks = SDL_GetTicks();

    m_eventLoopRunning = true;
    while (m_eventLoopRunning)
    {
        waitEvents();
        currentTicks = SDL_GetTicks();
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
    int scaling = m_video->getScaling();
    SDL_WarpMouse(x * scaling, y * scaling);
}
