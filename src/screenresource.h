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

#ifndef SCREEN_RESOURCE_H
#define SCREEN_RESOURCE_H

#include "image.h"
#include "resourcedata.h"

const unsigned int SCREEN_WIDTH       = 320;
const unsigned int SCREEN_HEIGHT      = 200;
const unsigned int BOOK_SCREEN_WIDTH  = 640;
const unsigned int BOOK_SCREEN_HEIGHT = 350;

class ScreenResource : public ResourceData
{
private:
    Image *m_image;
public:
    ScreenResource();
    virtual ~ScreenResource();
    Image* getImage();
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif

