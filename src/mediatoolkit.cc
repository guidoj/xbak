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
#include "mediatoolkit.h"
#include "sdl_toolkit.h"

MediaToolkit* MediaToolkit::m_instance = 0;

MediaToolkit::MediaToolkit()
    : m_audio(0)
    , m_clock(0)
    , m_video(0)
    , m_eventLoopRunning(false)
    , m_keyboardListeners()
    , m_pointerButtonListeners()
    , m_pointerMotionListeners()
    , m_timerListeners()
    , m_loopListeners()
{}

MediaToolkit::~MediaToolkit()
{
    m_keyboardListeners.clear();
    m_pointerButtonListeners.clear();
    m_pointerMotionListeners.clear();
    m_timerListeners.clear();
    m_loopListeners.clear();
}

MediaToolkit*
MediaToolkit::getInstance()
{
    if (!m_instance)
    {
        m_instance = new SDL_Toolkit();
    }
    return m_instance;
}

void
MediaToolkit::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

Audio*
MediaToolkit::getAudio() const
{
    return m_audio;
}

Clock*
MediaToolkit::getClock() const
{
    return m_clock;
}

Video*
MediaToolkit::getVideo() const
{
    return m_video;
}

void
MediaToolkit::addKeyboardListener(KeyboardEventListener *kel)
{
    m_keyboardListeners.push_back(kel);
}

void
MediaToolkit::removeKeyboardListener(KeyboardEventListener *kel)
{
    m_keyboardListeners.remove(kel);
}

void
MediaToolkit::addPointerButtonListener(PointerButtonEventListener *pbel)
{
    m_pointerButtonListeners.push_back(pbel);
}

void
MediaToolkit::removePointerButtonListener(PointerButtonEventListener *pbel)
{
    m_pointerButtonListeners.remove(pbel);
}

void
MediaToolkit::addPointerMotionListener(PointerMotionEventListener *pmel)
{
    m_pointerMotionListeners.push_back(pmel);
}

void
MediaToolkit::removePointerMotionListener(PointerMotionEventListener *pmel)
{
    m_pointerMotionListeners.remove(pmel);
}

void
MediaToolkit::addTimerListener(TimerEventListener *tel)
{
    m_timerListeners.push_back(tel);
}

void
MediaToolkit::removeTimerListener(TimerEventListener *tel)
{
    m_timerListeners.remove(tel);
}

void
MediaToolkit::addUpdateListener(LoopEventListener *lel)
{
    m_loopListeners.push_back(lel);
}

void
MediaToolkit::removeUpdateListener(LoopEventListener *lel)
{
    m_loopListeners.remove(lel);
}

void
MediaToolkit::terminateEventLoop()
{
    m_eventLoopRunning = false;
}
