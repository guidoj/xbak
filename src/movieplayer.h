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

#ifndef MOVIE_PLAYER_H
#define MOVIE_PLAYER_H

#include "movieresource.h"
#include "imageresource.h"
#include "paletteresource.h"
#include "soundresource.h"
#include "screenresource.h"

const unsigned int MAX_IMAGE_SLOTS   = 4;
const unsigned int MAX_PALETTE_SLOTS = 4;

class MoviePlayer
    : public KeyboardEventListener
    , public PointerButtonEventListener
    , public TimerEventListener
{
private:
    std::vector<MovieChunk *> *m_chunkVec;
    ScreenResource* m_screenSlot;
    SoundResource* m_soundSlot;
    ImageResource* m_imageSlot[MAX_IMAGE_SLOTS];
    PaletteResource* m_paletteSlot[MAX_PALETTE_SLOTS];
    Image *m_backgroundImage;
    bool m_backgroundImageDrawn;
    Image *m_savedImage;
    int m_xSavedImage;
    int m_ySavedImage;
    bool m_savedImageDrawn;
    unsigned int m_currFrame;
    unsigned int m_currImage;
    unsigned int m_currPalette;
    unsigned int m_currChunk;
    unsigned int m_currDelay;
    unsigned int m_currSound;
    std::map<unsigned int, int> m_soundMap;
    bool m_paletteActivated;
    bool m_playing;
    bool m_looped;
    bool m_delayed;
    void playChunk ( MediaToolkit* media );
public:
    MoviePlayer();
    ~MoviePlayer();
    void play ( std::vector<MovieChunk *> *movie, const bool repeat );
    void keyPressed ( const KeyboardEvent& kbe );
    void keyReleased ( const KeyboardEvent& kbe );
    void pointerButtonPressed ( const PointerButtonEvent& pbe );
    void pointerButtonReleased ( const PointerButtonEvent& pbe );
    void timerExpired ( const TimerEvent& te );
    void fadeComplete();
};

#endif
