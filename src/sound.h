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

#ifndef SOUND_H
#define SOUND_H

#include <map>

#include "filebuffer.h"

typedef enum _SoundFormat
{
    SF_MIDI,
    SF_WAVE,
    SF_UNKNOWN
} SoundFormat;

struct MidiEvent
{
    unsigned int delta;
    unsigned int size;
    uint8_t data[8];
};

class Sound
{
private:
    unsigned int m_type;
    unsigned int m_channel;
    SoundFormat m_format;
    FileBuffer *m_buffer;
    std::multimap<unsigned int, MidiEvent> m_midiEvents;
    void putVariableLength ( FileBuffer *buf, unsigned int n );
    void createWaveSamples ( FileBuffer *buf );
    void createMidiEvents ( FileBuffer *buf );
    void generateMidi();
    void generateWave();
public:
    Sound ( const unsigned int t );
    virtual ~Sound();
    unsigned int getType() const;
    unsigned int getChannel() const;
    SoundFormat getFormat() const;
    FileBuffer * getSamples();
    void addVoice ( FileBuffer *buf );
    void generateBuffer();
};

#endif
