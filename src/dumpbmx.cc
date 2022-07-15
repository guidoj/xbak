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

/*! \file dumpbmx.cc
    \brief Main dumpbmx source file.

    This file contains the the main function of the .BMX data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "imageresource.h"
#include "taggedimageresource.h"

int main ( int argc, char *argv[] )
{
    try
    {
        if ( ! ( ( argc == 2 ) || ( ( argc == 3 ) && ( std::string ( argv[2] ) == "TAG" ) ) ) )
        {
            std::cerr << "Usage: " << argv[0] << " <BMX-file> [TAG]" << std::endl;
            return 1;
        }
        if ( argc == 2 )
        {
            ImageResource *bmx = new ImageResource;
            FileManager::getInstance()->load ( bmx, argv[1] );
            for ( unsigned int i = 0; i < bmx->getNumImages(); i++ )
            {
                Image *image = bmx->getImage ( i );
                printf ( "%2d  %dx%d\n", i, image->getWidth(), image->getHeight() );
                for ( int y = 0; y < image->getHeight(); y++ )
                {
                    for ( int x = 0; x < image->getWidth(); x++ )
                    {
                        printf ( "%02x ", image->getPixel ( x, y ) );
                    }
                    printf ( "\n" );
                }
            }
            delete bmx;
            FileManager::cleanUp();
            Directories::cleanUp();
        }
        else
        {
            TaggedImageResource *bmx = new TaggedImageResource;
            FileManager::getInstance()->load ( bmx, argv[1] );
            for ( unsigned int i = 0; i < bmx->getNumImages(); i++ )
            {
                Image *image = bmx->getImage ( i );
                printf ( "%2d  %dx%d\n", i, image->getWidth(), image->getHeight() );
                for ( int y = 0; y < image->getHeight(); y++ )
                {
                    for ( int x = 0; x < image->getWidth(); x++ )
                    {
                        printf ( "%02x ", image->getPixel ( x, y ) );
                    }
                    printf ( "\n" );
                }
            }
            delete bmx;
            FileManager::cleanUp();
            Directories::cleanUp();
        }
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

