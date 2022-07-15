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

/*! \file dumppal.cc
    \brief Main dumppal source file.

    This file contains the the main function of the .PAL data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "paletteresource.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <PAL-file>" << std::endl;
            return 1;
        }
        PaletteResource *pal = new PaletteResource;
        FileManager::getInstance()->load(pal, argv[1]);
        for (unsigned int i = 0; i < pal->getPalette()->getSize(); i++)
        {
            printf("%3d #%02X%02X%02X\n", i, pal->getPalette()->getColor(i).r, pal->getPalette()->getColor(i).g, pal->getPalette()->getColor(i).b);
        }
        delete pal;
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

