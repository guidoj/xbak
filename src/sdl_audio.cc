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

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_sound.h>

#include "exception.h"
#include "sdl_audio.h"

const unsigned int AUDIO_FREQUENCY       = 11025;
const unsigned int AUDIO_FORMAT          = AUDIO_U8;
const unsigned int AUDIO_STEREO          = 2;
const unsigned int AUDIO_CHANNELS        = 8;
const unsigned int AUDIO_BUFFER_SIZE     = 4096;
const unsigned int AUDIO_RAW_BUFFER_SIZE = 16384;

SDL_mutex    *audioMutex;
Sound_Sample *audioSample[AUDIO_CHANNELS];

void ChannelDone(int channel)
{
    Mix_FreeChunk(Mix_GetChunk(channel));
    SDL_LockMutex(audioMutex);
    if (audioSample[channel])
    {
        Sound_FreeSample(audioSample[channel]);
        audioSample[channel] = 0;
    }
    SDL_UnlockMutex(audioMutex);
}

SDL_Audio::SDL_Audio()
{
    memset(audioSample, 0, sizeof(audioSample));
    audioMutex = SDL_CreateMutex();
    if (!audioMutex)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    Mix_Init(0);
    if (Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_STEREO, AUDIO_BUFFER_SIZE) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    Mix_AllocateChannels(AUDIO_CHANNELS);
    Mix_ChannelFinished(ChannelDone);
    if (Mix_VolumeMusic(90) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    if (!Sound_Init())
    {
        throw SDL_Exception(__FILE__, __LINE__, Sound_GetError());
    }
}

SDL_Audio::~SDL_Audio()
{
    Mix_HaltChannel(-1);
    if (!Sound_Quit())
    {
        throw SDL_Exception(__FILE__, __LINE__, Sound_GetError());
    }
    Mix_CloseAudio();
    Mix_Quit();
    if (audioMutex)
    {
        SDL_DestroyMutex(audioMutex);
    }
}

int SDL_Audio::playSound(FileBuffer *buffer, const int repeat)
{
    static Sound_AudioInfo info =
    {
        AUDIO_FORMAT, AUDIO_STEREO, AUDIO_FREQUENCY
    };
    buffer->rewind();
    SDL_RWops *rwops = SDL_RWFromMem(buffer->getCurrent(), buffer->getSize());
    if (!rwops)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    Sound_Sample *sample = Sound_NewSample(rwops, 0, &info, AUDIO_RAW_BUFFER_SIZE);
    if (!sample)
    {
        throw SDL_Exception(__FILE__, __LINE__, Sound_GetError());
    }
    unsigned int decoded = Sound_DecodeAll(sample);
    if (sample->flags & SOUND_SAMPLEFLAG_ERROR)
    {
        throw SDL_Exception(__FILE__, __LINE__, Sound_GetError());
    }
    Mix_Chunk *chunk = Mix_QuickLoad_RAW((Uint8*)sample->buffer, decoded);
    if (!chunk)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    int channel = Mix_PlayChannel(-1, chunk, repeat);
    if (channel < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    if (SDL_LockMutex(audioMutex) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    audioSample[channel] = sample;
    if (SDL_UnlockMutex(audioMutex) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    return channel;
}

void SDL_Audio::stopSound(const int channel)
{
    Mix_HaltChannel(channel);
}
