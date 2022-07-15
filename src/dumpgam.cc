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

/*! \file dumpgam.cc
    \brief Main dumpgam source file.

    This file contains the the main function of the saved game data dumper.
 */

#include <iostream>

#include "directories.h"
#include "exception.h"
#include "filemanager.h"
#include "gameresource.h"
#include "objectresource.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <GAM-file>" << std::endl;
            return 1;
        }
        GameResource *gam = new GameResource;
        FileManager::getInstance()->load(gam, argv[1]);
        Game *game = gam->getGame();
        printf("%s  l: (%d, %d) z: %d  c: (%d, %d)  p: (%d, %d)  o: %d\n",
               game->getName().c_str(), gam->getXLoc(), gam->getYLoc(), gam->getZone(),
               game->getCamera()->getPosition().getCell().getX(), game->getCamera()->getPosition().getCell().getY(),
               game->getCamera()->getPos().getX(), game->getCamera()->getPos().getY(), game->getCamera()->getHeading());
        for (unsigned int m = 0; m < game->getParty()->getNumMembers(); m++)
        {
            printf("%-10s:", game->getParty()->getMember(m)->getName().c_str());
            for (unsigned int i = 0; i < NUM_STATS; i++)
            {
                printf("\n\t");
                for (unsigned int j = 0; j < NUM_STAT_VALUES; j++)
                {
                    printf(" %3d", game->getParty()->getMember(m)->getStatistics().get(i, j));
                }
            }
            printf("\n");
            Inventory *inv = game->getParty()->getMember(m)->getInventory();
            for (unsigned int i = 0; i < inv->getSize(); i++)
            {
                const InventoryItem *item = inv->getItem(i);
                printf("\t%-24s %3d\n", ObjectResource::getInstance()->getObjectInfo(item->getId()).name.c_str(), item->getValue());
            }
        }
        printf("active:");
        for (unsigned int i = 0; i < game->getParty()->getNumActiveMembers(); i++)
        {
            printf(" %s", game->getParty()->getActiveMember(i)->getName().c_str());
        }
        printf("\n");
        delete gam;
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

