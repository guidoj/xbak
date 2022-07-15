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

#include "defines.h"
#include "spriteobject.h"

SpriteObject::SpriteObject(const Vector2D &p, Image *img)
    : GenericObject(p)
    , m_sprite(img)
{
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::calculateRelativePosition(const Vector2D &p)
{
    m_pos.calculateRelativePosition(p);
}

bool SpriteObject::isInView(const Angle & heading, unsigned int & distance)
{
    if (m_pos.isInView(heading))
    {
        distance = m_pos.getDistance();
        return true;
    }
    return false;
}

void SpriteObject::drawFirstPerson(const int x, const int y, const int w, const int h, Camera *cam)
{
    Image *image = new Image((int)((double)m_sprite->getWidth() * m_pos.getDistanceFactor()), (int)((double)m_sprite->getHeight() * m_pos.getDistanceFactor()), m_sprite);
    Vector2D v = m_pos.toFirstPerson(w, h, cam->getOrientation().getAngle());
    int ww = MIN(image->getWidth(), w - v.getX());
    int hh = image->getHeight();
    image->draw(x + v.getX(), y + v.getY() - hh, 0, 0, ww, hh, 0);
    delete image;
}

void SpriteObject::drawTopDown()
{
}
