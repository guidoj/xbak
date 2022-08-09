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

#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "genericobject.h"
#include "image.h"

class SpriteObject
    : public GenericObject
{
private:
    Image *m_sprite;
public:
    SpriteObject ( const Vector2D &p, Image *img );
    virtual ~SpriteObject();
    void calculateRelativePosition ( const Vector2D &p );
    bool isInView ( const Angle & heading, unsigned int & distance );
    void drawFirstPerson ( const int x, const int y, const int w, const int h, Camera *cam );
    void drawTopDown();
};

#endif
