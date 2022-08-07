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

#include <SDL_mixer.h>

#include "exception.h"
#include "sdl_audio.h"

const unsigned int AUDIO_FREQUENCY       = 11025;
const unsigned int AUDIO_FORMAT          = AUDIO_U8;
const unsigned int AUDIO_STEREO          = 2;
const unsigned int AUDIO_CHANNELS        = 8;
const unsigned int AUDIO_BUFFER_SIZE     = 4096;
const unsigned int AUDIO_RAW_BUFFER_SIZE = 16384;

Mix_Music *playingMusic;
bool processingChannelDone = false;

static void MusicDone(void)
{
    if (playingMusic != 0)
    {
        Mix_FreeMusic( playingMusic );
        playingMusic = 0;
    }
}

static void ChannelDone(int channel)
{
    if (!processingChannelDone)
    {
        processingChannelDone = true;
        if (channel < 0)
        {
            throw DataCorruption(__FILE__, __LINE__);
        }
        Mix_Chunk *chunk = Mix_GetChunk(channel);
        if (chunk != 0)
        {
            Mix_FreeChunk(chunk);
        }
        processingChannelDone = false;
    }
}

SDL_Audio::SDL_Audio()
{
    if ((Mix_Init(MIX_INIT_MID) & MIX_INIT_MID) == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, "No MIDI support!");
    }
    if (Mix_SetTimidityCfg("./timidity/timidity.cfg") == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    if (Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_STEREO, AUDIO_BUFFER_SIZE) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    if (Mix_AllocateChannels(AUDIO_CHANNELS) != AUDIO_CHANNELS)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    Mix_ChannelFinished(ChannelDone);
    Mix_HookMusicFinished(MusicDone);
    if (Mix_Volume(-1, 90) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    if (Mix_VolumeMusic(90) < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
}

SDL_Audio::~SDL_Audio()
{
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    Mix_CloseAudio();
    Mix_Quit();
}

int SDL_Audio::playMusic(FileBuffer *buffer, const int repeat)
{
    if (!Mix_PlayingMusic())
    {
        buffer->rewind();
        SDL_RWops *rwops = SDL_RWFromMem(buffer->getCurrent(), buffer->getSize());
        if (!rwops)
        {
            throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
        }
        Mix_Music *music = Mix_LoadMUS_RW(rwops, 1);
        if (!music)
        {
            throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
        }
        if (Mix_PlayMusic(music, repeat))
        {
            throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
        }
        playingMusic = music;
    }
    return AUDIO_CHANNELS;
}

int SDL_Audio::playSound(FileBuffer *buffer, const int repeat)
{
    buffer->rewind();
    SDL_RWops *rwops = SDL_RWFromMem(buffer->getCurrent(), buffer->getSize());
    if (!rwops)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    Mix_Chunk *chunk = Mix_LoadWAV_RW(rwops, 1);
    if (!chunk)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    int channel = Mix_PlayChannel(-1, chunk, repeat);
    if (channel < 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, Mix_GetError());
    }
    return channel;
}

void SDL_Audio::stopMusic(void)
{
    Mix_HaltMusic();
}

void SDL_Audio::stopSound(const int channel)
{
    Mix_HaltChannel(channel);
}
