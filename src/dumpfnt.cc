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

/*! \file dumpfnt.cc
    \brief Main dumpfnt source file.

    This file contains the the main function of the .FNT data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "fontresource.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <FNT-file>" << std::endl;
            return 1;
        }
        FontResource *fnt = new FontResource;
        FileManager::getInstance()->load(fnt, argv[1]);
        Font *font = fnt->getFont();
        for (unsigned int i = 0; i < font->getSize(); i++)
        {
            printf("%2d: '%c' (%d)\n", i, i + font->getFirst(), font->getWidth(i));
            FontGlyph glyph = font->getGlyph(i);
            for (int j = 0; j < font->getHeight(); j++)
            {
                for (unsigned int k = 0; k < glyph.width; k++)
                {
                    printf("%c", glyph.data[j] & (0x8000 >> k) ? '*' : '.');
                }
                printf("\n");
            }
        }
        delete fnt;
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

