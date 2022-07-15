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

/*! \file dumpddx.cc
    \brief Main dumpddx source file.

    This file contains the the main function of the .DDX data dumper.
 */

#include <iostream>

#include "dialogresource.h"
#include "directories.h"
#include "exception.h"
#include "filemanager.h"

void dumpDialogData(unsigned int n, DialogData *data, unsigned int depth)
{
    for (unsigned int d = 0; d < depth; d++)
    {
        printf("\t");
    }
    printf("%d\t%d\n", n, data->m_childDialogs);
    for (unsigned int i = 0; i < data->m_text.size(); i++)
    {
        for (unsigned int d = 0; d < depth; d++)
        {
            printf("\t");
        }
        printf("\t%d: %s\n", i, data->m_text[i].c_str());
    }
    for (unsigned int i = 0; i < data->m_childData.size(); i++)
    {
        dumpDialogData(i, data->m_childData[i], depth+1);
    }
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <DDX-file>" << std::endl;
            return 1;
        }
        DialogResource *ddx = new DialogResource;
        FileManager::getInstance()->load(ddx, argv[1]);
        printf("Size: %d\n", ddx->getSize());
        DialogData* data = 0;
        for (unsigned int i = 0; i < 512; i++)
        {
            if (ddx->find(i, data))
            {
                dumpDialogData(i, data, 0);
            }
        }
        delete ddx;
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

