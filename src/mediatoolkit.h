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

#ifndef MEDIA_TOOLKIT_H
#define MEDIA_TOOLKIT_H

#include <list>

#include "audio.h"
#include "clock.h"
#include "eventlistener.h"
#include "video.h"

class MediaToolkit
{
private:
    static MediaToolkit* m_instance;
protected:
    Audio *m_audio;
    Clock *m_clock;
    Video *m_video;
    bool m_eventLoopRunning;
    std::list<KeyboardEventListener *> m_keyboardListeners;
    std::list<PointerButtonEventListener *> m_pointerButtonListeners;
    std::list<PointerMotionEventListener *> m_pointerMotionListeners;
    std::list<TimerEventListener *> m_timerListeners;
    std::list<LoopEventListener *> m_loopListeners;
public:
    MediaToolkit();
    virtual ~MediaToolkit();
    static MediaToolkit* getInstance();
    static void cleanUp();
    Audio* getAudio() const;
    Clock* getClock() const;
    Video* getVideo() const;
    void addKeyboardListener ( KeyboardEventListener *kel );
    void removeKeyboardListener ( KeyboardEventListener *kel );
    void addPointerButtonListener ( PointerButtonEventListener *pbel );
    void removePointerButtonListener ( PointerButtonEventListener *pbel );
    void addPointerMotionListener ( PointerMotionEventListener *pmel );
    void removePointerMotionListener ( PointerMotionEventListener *pmel );
    void addTimerListener ( TimerEventListener *tel );
    void removeTimerListener ( TimerEventListener *tel );
    void addUpdateListener ( LoopEventListener *lel );
    void removeUpdateListener ( LoopEventListener *lel );
    void terminateEventLoop();
    virtual void pollEvents() = 0;
    virtual void pollEventLoop() = 0;
    virtual void waitEvents() = 0;
    virtual void waitEventLoop() = 0;
    virtual void clearEvents() = 0;
    virtual void getPointerPosition ( int *x, int *y ) = 0;
    virtual void setPointerPosition ( int x, int y ) = 0;
};

#endif
