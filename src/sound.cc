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

#include <cstring>

#include "exception.h"
#include "sound.h"

Sound::Sound(const unsigned int t)
    : m_type(t)
    , m_channel(255)
    , m_format(SF_UNKNOWN)
    , m_buffer()
    , m_midiEvents()
{
}

Sound::~Sound()
{
    delete m_buffer;
    m_midiEvents.clear();
}

unsigned int Sound::getType() const
{
    return m_type;
}

unsigned int Sound::getChannel() const
{
    return m_channel;
}

SoundFormat Sound::getFormat() const
{
    return m_format;
}

FileBuffer * Sound::getSamples()
{
    return m_buffer;
}

/* WAVE/RIFF tags & constants */
const uint32_t RIFF_ID         = 0x46464952;
const uint32_t WAVE_ID         = 0x45564157;
const uint32_t FMT_ID          = 0x20746d66;
const uint32_t DATA_ID         = 0x61746164;

void Sound::createWaveSamples(FileBuffer *buf)
{
    buf->skip(1);
    unsigned int rate = buf->getUint16LE();
    unsigned int size = buf->getUint32LE();
    buf->skip(2);
    m_buffer = new FileBuffer(12 + 8 + 16 + 8 + size);
    m_buffer->putUint32LE(RIFF_ID);
    m_buffer->putUint32LE(m_buffer->getSize() - 8);
    m_buffer->putUint32LE(WAVE_ID);
    m_buffer->putUint32LE(FMT_ID);
    m_buffer->putUint32LE(16);      // chunk size
    m_buffer->putUint16LE(1);       // compression: 1 = uncompressed PCM
    m_buffer->putUint16LE(1);       // # channels
    m_buffer->putUint32LE(rate);    // sample rate
    m_buffer->putUint32LE(rate);    // average bytes per sec: sample rate * block align
    m_buffer->putUint16LE(1);       // block align: significant bits per sample / 8 * # channels
    m_buffer->putUint16LE(8);       // significant bits per sample
    m_buffer->putUint32LE(DATA_ID);
    m_buffer->putUint32LE(size);
    m_buffer->copyFrom(buf, size);
    m_buffer->rewind();
}

void Sound::generateWave()
{
}

/* Standard MIDI File tags & constants */
const uint32_t SMF_HEADER      = 0x6468544d;
const uint32_t SMF_TRACK       = 0x6b72544d;
const uint16_t SMF_FORMAT      = 0;
const uint32_t SMF_HEADER_SIZE = 6;
const uint16_t SMF_PPQN        = 32;

/* MIDI event codes */
const uint8_t MIDI_NOTE_OFF  = 0x80;
const uint8_t MIDI_NOTE_ON   = 0x90;
const uint8_t MIDI_KEY       = 0xa0;
const uint8_t MIDI_CONTROL   = 0xb0;
const uint8_t MIDI_PATCH     = 0xc0;
const uint8_t MIDI_CHANNEL   = 0xd0;
const uint8_t MIDI_PITCH     = 0xe0;
const uint8_t MIDI_SYSEX     = 0xf0;
const uint8_t MIDI_TIMING    = 0xf8;
const uint8_t MIDI_SEQ_START = 0xfa;
const uint8_t MIDI_SEQ_CONT  = 0xfb;
const uint8_t MIDI_SEQ_END   = 0xfc;
const uint8_t MIDI_META      = 0xff;

/* MIDI Meta events */
const uint8_t META_SEQNUM     = 0x00;
const uint8_t META_TEXT       = 0x01;
const uint8_t META_COPYRIGHT  = 0x02;
const uint8_t META_TRACK      = 0x03;
const uint8_t META_INSTRUMENT = 0x04;
const uint8_t META_LYRIC      = 0x05;
const uint8_t META_MARKER     = 0x06;
const uint8_t META_CUE        = 0x07;
const uint8_t META_CHANNEL    = 0x20;
const uint8_t META_PORT       = 0x21;
const uint8_t META_EOT        = 0x2f;
const uint8_t META_TEMPO      = 0x51;
const uint8_t META_SMPTE      = 0x54;
const uint8_t META_TIME       = 0x58;
const uint8_t META_KEY        = 0x59;
const uint8_t META_SEQDATA    = 0x7f;

void Sound::putVariableLength(FileBuffer *buf, unsigned int n)
{
    unsigned int tmp = (n & 0x7f);
    unsigned int k = 1;
    while (n >>= 7)
    {
        tmp <<= 8;
        tmp |= ((n & 0x7f) | 0x80);
        k++;
    }
    while (k--)
    {
        buf->putUint8(tmp & 0xff);
        tmp >>= 8;
    }
}

void Sound::createMidiEvents(FileBuffer *buf)
{
    unsigned int delta;
    unsigned int code;
    unsigned int mode = 0;
    unsigned int tick = 0;

    buf->skip(1);
    while ((mode != MIDI_SEQ_END) && !buf->atEnd())
    {
        delta = 0;
        code = buf->getUint8();
        while (code == MIDI_TIMING)
        {
            delta += 240;
            code = buf->getUint8();
        }
        delta += code;
        code = buf->getUint8();
        if (((code & 0xf0) == MIDI_NOTE_ON) ||
                ((code & 0xf0) == MIDI_CONTROL) ||
                ((code & 0xf0) == MIDI_PATCH)  ||
                ((code & 0xf0) == MIDI_PITCH))
        {
            mode = code;
            if ((code & 0x0f) != m_channel)
            {
                throw DataCorruption(__FILE__, __LINE__);
            }
        }
        else if (code == MIDI_SEQ_END)
        {
            mode = code;
        }
        else
        {
            buf->skip(-1);
        }
        if (mode != MIDI_SEQ_END)
        {
            MidiEvent me;
            memset(&me, 0, sizeof(MidiEvent));
            me.data[0] = mode;
            switch (mode & 0xf0)
            {
            case MIDI_NOTE_ON:
                me.data[1] = buf->getUint8();
                me.data[2] = buf->getUint8();
                if (me.data[2] == 0)
                {
                    me.data[0] = MIDI_NOTE_OFF | m_channel;
                }
                me.size = 3;
                break;
            case MIDI_CONTROL:
            case MIDI_PITCH:
                me.data[1] = buf->getUint8();
                me.data[2] = buf->getUint8();
                me.size = 3;
                break;
            case MIDI_PATCH:
                me.data[1] = buf->getUint8();
                me.size = 2;
                break;
            default:
                if (mode == MIDI_SEQ_END)
                {
                    me.size = 1;
                }
                else
                {
                    throw DataCorruption(__FILE__, __LINE__);
                }
                break;
            }
            tick += delta;
            m_midiEvents.insert(std::pair<unsigned int, MidiEvent>(tick, me));
        }
    }
}

void Sound::generateMidi()
{
    unsigned int size = 0;
    unsigned int tick = 0;
    for (std::multimap<unsigned int, MidiEvent>::iterator it = m_midiEvents.begin(); it != m_midiEvents.end(); ++it)
    {
        MidiEvent& me = it->second;
        me.delta = it->first - tick;
        size += 1;
        if (me.delta >= (1 << 7))
        {
            size += 1;
        }
        if (me.delta >= (1 << 14))
        {
            size += 1;
        }
        if (me.delta >= (1 << 21))
        {
            size += 1;
        }
        size += me.size;
        tick = it->first;
    }
    m_buffer = new FileBuffer(8 + SMF_HEADER_SIZE + 8 + size + 4);
    m_buffer->putUint32LE(SMF_HEADER);
    m_buffer->putUint32BE(SMF_HEADER_SIZE);
    m_buffer->putUint16BE(SMF_FORMAT);
    m_buffer->putUint16BE(1);
    m_buffer->putUint16BE(SMF_PPQN);
    m_buffer->putUint32LE(SMF_TRACK);
    m_buffer->putUint32BE(size);
    for (std::multimap<unsigned int, MidiEvent>::iterator it = m_midiEvents.begin(); it != m_midiEvents.end(); ++it)
    {
        MidiEvent& me = it->second;
        putVariableLength(m_buffer, me.delta);
        for (unsigned int i = 0; i < me.size; i++)
        {
            m_buffer->putUint8(me.data[i]);
        }
    }
    m_midiEvents.clear();
    m_buffer->putUint8(0);
    m_buffer->putUint8(MIDI_META);
    m_buffer->putUint8(META_EOT);
    m_buffer->putUint8(0);
    m_buffer->rewind();
}

void Sound::addVoice(FileBuffer *buf)
{
    unsigned int code = buf->getUint8();
    m_channel = code & 0x0f;
    if (code == 0xfe)
    {
        m_format = SF_WAVE;
        createWaveSamples(buf);
    }
    else
    {
        m_format = SF_MIDI;
        createMidiEvents(buf);
    }
}

void Sound::generateBuffer()
{
    if (m_format == SF_MIDI)
    {
        generateMidi();
    }
}
