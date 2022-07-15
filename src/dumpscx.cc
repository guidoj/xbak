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

/*! \file dumpscx.cc
    \brief Main dumpscx source file.

    This file contains the the main function of the .SCX data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "screenresource.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <SCX-file>" << std::endl;
            return 1;
        }
        ScreenResource *scx = new ScreenResource;
        FileManager::getInstance()->load(scx, argv[1]);
        Image *image = scx->getImage();
        printf("%dx%d\n", image->getWidth(), image->getHeight());
        for (int y = 0; y < image->getHeight(); y++)
        {
            for (int x = 0; x < image->getWidth(); x++)
            {
                printf("%02x ", image->getPixel(x, y));
            }
            printf("\n");
        }
        delete scx;
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

