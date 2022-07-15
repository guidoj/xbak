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

#ifndef IMAGE_WIDGET_H
#define IMAGE_WIDGET_H

#include "image.h"
#include "widget.h"

typedef enum _Flipping
{
    NONE, HORIZONTAL, VERTICAL
} Flipping;

class ImageWidget
    : public Widget
{
private:
    Image *m_image;
public:
    ImageWidget ( const Rectangle &r, Image *img );
    virtual ~ImageWidget();
    void horizontalFlip();
    void verticalFlip();
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
