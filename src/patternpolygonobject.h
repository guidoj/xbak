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

#ifndef PATTERN_POLYGON_OBJECT_H
#define PATTERN_POLYGON_OBJECT_H

#include "polygonobject.h"
#include "image.h"

class PatternPolygonObject
    : public PolygonObject
{
private:
    const Image *m_texture;
public:
    PatternPolygonObject( const Vector2D& p, const Image *image );
    virtual ~PatternPolygonObject();
    void drawFirstPerson ( const int x, const int y, const int w, const int h, Camera *cam );
    void drawTopDown();
};

#endif
