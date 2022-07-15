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

/*! \file dumpsnd.cc
    \brief Main dumpsnd source file.

    This file contains the the main function of the midi data dumper.
 */

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "sound.h"
#include "soundresource.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            printf("Usage: %s <sound-id>\n", argv[0]);
            return 1;
        }
        SoundResource *snd = SoundResource::getInstance();
        SoundData data = snd->getSoundData(atoi(argv[1]));
        printf("%8s %d %d\n", data.name.c_str(), data.type, (unsigned int)data.sounds.size());
        for (unsigned int i = 0; i < data.sounds.size(); i++)
        {
            Sound *sound = data.sounds[i];
            printf("%d: %d %d %d\n", i, sound->getType(),sound->getChannel(), sound->getFormat());
            FileBuffer *buf = sound->getSamples();
            buf->dump();
        }
        delete snd;
        SoundResource::cleanUp();
        FileManager::cleanUp();
        Directories::cleanUp();
    }
    catch (Exception &e)
    {
        e.print("main");
    }
    catch (...)
    {
        /* every exception should have been handled before */
        std::cerr << "Unhandled exception" << std::endl;
    }
    return 0;
}

