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

/*! \file dumplbl.cc
    \brief Main dumplbl source file.

    This file contains the the main function of the LBL_*.DAT data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "labelresource.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <LBL-file>" << std::endl;
            return 1;
        }
        LabelResource *lbl = new LabelResource;
        FileManager::getInstance()->load(lbl, argv[1]);
        for (unsigned int i = 0; i < lbl->getSize(); i++)
        {
            LabelData data = lbl->getLabelData(i);
            printf("%3d: %3d %3d %3d %3d %3d %s\n", i,
                   data.xpos, data.ypos, data.type, data.color, data.shadow, data.label.c_str());
        }
        delete lbl;
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

