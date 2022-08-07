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

/*! \file resourcedemo.cc
    \brief Main source file for the resource demo.

    This file contains the the main function of resource demo.
 */

#include <cstdlib>
#include <cstring>
#include <iostream>

#if defined( __MACOS__) || defined(__MACOSX__) || defined(__APPLE__) || defined(__APPLE_CC__)
#include "SDL.h"
#endif

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "testapplication.h"

typedef enum _CommandType
{
    CT_UNKNOWN,
    CT_BMX,
    CT_FNT,
    CT_RMF,
    CT_SCX,
    CT_SND,
    CT_TTM,
    CT_WLD
} CommandType;

CommandType
get_command_type ( char *cmd )
{
    if ( !cmd )
    {
        return CT_UNKNOWN;
    }
    if ( strncmp ( cmd, "BMX", 3 ) == 0 )
    {
        return CT_BMX;
    }
    if ( strncmp ( cmd, "FNT", 3 ) == 0 )
    {
        return CT_FNT;
    }
    if ( strncmp ( cmd, "RMF", 3 ) == 0 )
    {
        return CT_RMF;
    }
    if ( strncmp ( cmd, "SCX", 3 ) == 0 )
    {
        return CT_SCX;
    }
    if ( strncmp ( cmd, "SND", 3 ) == 0 )
    {
        return CT_SND;
    }
    if ( strncmp ( cmd, "TTM", 3 ) == 0 )
    {
        return CT_TTM;
    }
    if ( strncmp ( cmd, "WLD", 3 ) == 0 )
    {
        return CT_WLD;
    }
    return CT_UNKNOWN;
}

int main ( int argc, char **argv )
{
    try
    {
        CommandType ct = get_command_type ( argv[1] );
        switch ( ct )
        {
        case CT_UNKNOWN:
            printf ( "Usage: %s <BMX|FNT|RMF|SCX|SND|TTM|WLD> <command-options>\n", argv[0] );
            return -1;
        case CT_BMX:
            if ( ! ( ( argc == 4 ) || ( ( argc == 5 ) && ( std::string ( argv[4] ) == "TAG" ) ) ) )
            {
                printf ( "Usage: %s BMX <PAL-file> <BMX-file> [TAG]\n", argv[0] );
                return -1;
            }
            else
            {
                TestApplication *app = TestApplication::getInstance();
                app->activatePalette ( argv[2] );
                if ( argc == 4 )
                {
                    app->showImage ( argv[3] );
                }
                else
                {
                    app->showTaggedImage ( argv[3] );
                }
            }
            break;
        case CT_FNT:
            if ( argc != 3 )
            {
                printf ( "Usage: %s FNT <FNT-file>\n", argv[0] );
                return -1;
            }
            else
            {
                TestApplication *app = TestApplication::getInstance();
                app->activatePalette();
                app->drawFont ( argv[2] );
            }
            break;
        case CT_RMF:
            if ( argc != 3 )
            {
                printf ( "Usage: %s RMF <A|E>\n", argv[0] );
                return -1;
            }
            else
            {
                switch ( *argv[2] )
                {
                case 'A':
                    FileManager::getInstance()->archiveAllResources();
                    break;
                case 'E':
                    FileManager::getInstance()->extractAllResources();
                    break;
                default:
                    printf ( "Usage: %s RMF <A|E>\n", argv[0] );
                    return -1;
                    break;
                }
                FileManager::cleanUp();
            }
            break;
        case CT_SCX:
            if ( argc != 4 )
            {
                printf ( "Usage: %s SCX <PAL-file> <SCX-file>\n", argv[0] );
                return -1;
            }
            else
            {
                TestApplication *app = TestApplication::getInstance();
                app->activatePalette ( argv[2] );
                app->showScreen ( argv[3] );
            }
            break;
        case CT_SND:
            if ( argc != 3 )
            {
                printf ( "Usage: %s SND <index>\n", argv[0] );
                return -1;
            }
            else
            {
                TestApplication *app = TestApplication::getInstance();
                app->playSound ( atoi ( argv[2] ) );
            }
            break;
        case CT_TTM:
            if ( argc != 3 )
            {
                printf ( "Usage: %s TTM <TTM-file>\n", argv[0] );
                return -1;
            }
            else
            {
                TestApplication *app = TestApplication::getInstance();
                app->activatePalette();
                app->playMovie ( argv[2] );
            }
            break;
        case CT_WLD:
            if ( argc != 4 )
            {
                printf ( "Usage: %s WLD <zone> <tile>\n", argv[0] );
                return -1;
            }
            else
            {
                TestApplication *app = TestApplication::getInstance();
                app->activatePalette ( "Z" + std::string ( argv[2] ) + ".PAL" );
                app->walkWorld ( argv[2], argv[3] );
            }
            break;
        }
        TestApplication::cleanUp();
        Directories::cleanUp();
    }
    catch ( Exception &e )
    {
        e.print ( "main" );
    }
    catch ( ... )
    {
        /* every exception should have been handled before */
        std::cerr << "Unhandled exception" << std::endl;
    }
    return 0;
}
