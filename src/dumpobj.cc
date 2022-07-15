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

/*! \file dumpobj.cc
    \brief Main dumpobj source file.

    This file contains the the main function of the OBJINFO.DAT data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "objectresource.h"

int main()
{
    try
    {
        for (unsigned int i = 0; i < ObjectResource::getInstance()->getSize(); i++)
        {
            ObjectInfo info = ObjectResource::getInstance()->getObjectInfo(i);
            printf("%-30s: %04x %3d %5d %3d %3d %3d %3d %1d %1d %2d %04x %6d %04x %3d\n", info.name.c_str(), info.flags, info.level, info.value,
                   info.strengthSwing, info.accuracySwing, info.strengthThrust, info.accuracyThrust, info.imageSize, info.race, info.type,
                   info.effectMask, info.effect, info.modifierMask, info.modifier);
        }
        ObjectResource::cleanUp();
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

