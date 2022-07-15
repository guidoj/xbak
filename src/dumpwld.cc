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

/*! \file dumpwld.cc
    \brief Main dumpwld source file.

    This file contains the the main function of the .WLD data dumper.
 */

#include <cstring>
#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "tileworldresource.h"

const unsigned int MAP_SIZE_X = 96;
const unsigned int MAP_SIZE_Y = 96;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <WLD-file>" << std::endl;
            return 1;
        }
        TileWorldResource *wld = new TileWorldResource;
        FileManager::getInstance()->load(wld, argv[1]);
        printf("%d %d %d %d %d\n", wld->getSize(), wld->getMinX(), wld->getMaxX(), wld->getMinY(), wld->getMaxY());
        unsigned int deltaX = wld->getMaxX() - wld->getMinX();
        unsigned int deltaY = wld->getMaxY() - wld->getMinY();
        uint8_t *map = new uint8_t[MAP_SIZE_X * MAP_SIZE_Y];
        memset(map, 0, MAP_SIZE_X * MAP_SIZE_Y);
        for (unsigned int i = 0; i < wld->getSize(); i++)
        {
            TileWorldItem mi = wld->getItem(i);
            printf("%6d,%6d: %3d (%02x) %08x\n", mi.xloc, mi.yloc, mi.type, mi.type, mi.flags);
            if (mi.type > 0)
            {
                unsigned int x = (mi.xloc - wld->getMinX()) * MAP_SIZE_X / deltaX;
                unsigned int y = (mi.yloc - wld->getMinY()) * MAP_SIZE_Y / deltaY;
                map[x + y * MAP_SIZE_X] = mi.type;
            }
        }
        for (unsigned int y = 0; y < MAP_SIZE_Y; y++)
        {
            for (unsigned int x = 0; x < MAP_SIZE_X; x++)
            {
                uint8_t m = map[x + y * MAP_SIZE_X];
                if (m > 0)
                {
                    printf("%02x", m);
                }
                else
                {
                    printf("--");
                }
            }
            printf("\n");
        }
        delete[] map;
        delete wld;
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

