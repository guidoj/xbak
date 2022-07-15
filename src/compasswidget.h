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

#ifndef COMPASS_WIDGET_H
#define COMPASS_WIDGET_H

#include "camera.h"
#include "image.h"
#include "observer.h"
#include "widget.h"

class CompassWidget
    : public Observer
    , public Widget
{
private:
    Camera *m_camera;
    Image *m_compassImage;
    Image *m_cachedImage;
public:
    CompassWidget ( Camera *cam, Image *img );
    virtual ~CompassWidget();
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
    void update();
};

#endif

