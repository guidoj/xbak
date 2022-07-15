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

/*! \file dumpads.cc
    \brief Main dumpads source file.

    This file contains the the main function of the .ADS data dumper.
 */

#include <iostream>

#include "animationresource.h"
#include "directories.h"
#include "exception.h"
#include "filemanager.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <ADS-file>" << std::endl;
            return 1;
        }
        AnimationResource *anim = new AnimationResource;
        FileManager::getInstance()->load(anim, argv[1]);
        AnimationData data = anim->getAnimationData(1);
        printf("%s %s %s\n", anim->getVersion().c_str(), data.m_name.c_str(), data.m_resource.c_str());
        FileBuffer *scr = anim->getScript();
        while (!scr->atEnd())
        {
            unsigned int code = scr->getUint16LE();
            printf("%04x ", code);
            switch (code)
            {
            case 0x0001:
            case 0x0002:
            case 0x0003:
            case 0x0004:
            case 0x0005:
            case 0x0006:
            case 0x0007:
            case 0x0008:
            case 0x0009:
            case 0x000a:
            case 0x000b:
            case 0x000c:
            case 0x000d:
            case 0x000e:
            case 0x000f:
            case 0x0010:
            case 0x0011:
            case 0x0012:
            case 0x0013:
            case 0x0014:
            case 0x0015:
            case 0x0016:
            case 0x0017:
            case 0x0018:
            case 0x0019:
            case 0x001a:
            case 0x001b:
            case 0x001c:
            case 0x001d:
            case 0x001e:
            case 0x001f:
                break;
            case 0x1030:
                printf(" %d %d", scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0x1330:
                printf(" %d %d", scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0x1350:
                printf(" %d %d", scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0x13a0:
                printf(" %d %d", scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0x13b0:
                printf(" %d %d", scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0x1420:
                break;
            case 0x1500:
                break;
            case 0x1510:
                break;
            case 0x1520:
                break;
            case 0x2000:
                printf(" %d %d %d %d", scr->getUint16LE(), scr->getUint16LE(), scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0x2005:
                printf(" %d %d %d %d", scr->getUint16LE(), scr->getUint16LE(), scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0x2010:
                printf(" %d %d %d", scr->getUint16LE(), scr->getUint16LE(), scr->getUint16LE());
                break;
            case 0xffff:
                break;
            default:
                printf(" unknown");
                break;
            }
            printf("\n");
        }
        delete anim;
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

