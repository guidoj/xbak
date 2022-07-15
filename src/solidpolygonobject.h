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

#ifndef SOLID_POLYGON_OBJECT_H
#define SOLID_POLYGON_OBJECT_H

#include "polygonobject.h"
#include "image.h"

class SolidPolygonObject
    : public PolygonObject
{
private:
    const unsigned int m_color;
public:
    SolidPolygonObject( const Vector2D& p, const unsigned int c );
    ~SolidPolygonObject();
    void drawFirstPerson ( const int x, const int y, const int w, const int h, Camera *cam );
    void drawTopDown();
};

#endif
