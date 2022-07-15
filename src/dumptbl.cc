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

/*! \file dumptbl.cc
    \brief Main dumptbl source file.

    This file contains the the main function of the .TBL data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "tableresource.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <TBL-file>" << std::endl;
            return 1;
        }
        TableResource *tbl = new TableResource;
        FileManager::getInstance()->load(tbl, argv[1]);
        for (unsigned int i = 0; i < tbl->getMapSize(); i++)
        {
            GidInfo *gid = tbl->getGidItem(i);
            DatInfo *dat = tbl->getDatItem(i);
            printf("%3d: %-8s (%6d %6d) %04x %02x %2d %2d %2d %2d\n",
                   i, tbl->getMapItem(i).c_str(), gid->xradius, gid->yradius, gid->flags,
                   dat->entityFlags, dat->entityType, dat->terrainType, dat->terrainClass, dat->sprite);
            printf("\t(%6d, %6d, %6d)  (%6d, %6d, %6d)  (%6d, %6d, %6d)\n",
                   dat->min.getX(), dat->min.getY(), dat->min.getZ(),
                   dat->max.getX(), dat->max.getY(), dat->max.getZ(),
                   dat->pos.getX(), dat->pos.getY(), dat->pos.getZ());
            for (unsigned int j = 0; j < gid->textureCoords.size(); j++)
            {
                printf("\t\t(%4d, %4d)\n",
                       gid->textureCoords[j]->getX(), gid->textureCoords[j]->getY());
            }
            for (unsigned int j = 0; j < gid->otherCoords.size(); j++)
            {
                printf("\t\t(%6d, %6d)\n",
                       gid->otherCoords[j]->getX(), gid->otherCoords[j]->getY());
            }
            for (unsigned int j = 0; j < dat->vertices.size(); j++)
            {
                printf("\t\t(%6d, %6d, %6d)\n",
                       dat->vertices[j]->getX(), dat->vertices[j]->getY(), dat->vertices[j]->getZ());
            }
        }
        delete tbl;
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
