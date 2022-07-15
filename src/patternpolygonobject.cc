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

#include "mediatoolkit.h"
#include "patternpolygonobject.h"

PatternPolygonObject::PatternPolygonObject(const Vector2D& p, const Image *image)
    : PolygonObject(p)
    , m_texture(image)
{
}

PatternPolygonObject::~PatternPolygonObject()
{
}

void PatternPolygonObject::drawFirstPerson(const int x, const int y, const int w, const int h, Camera *cam)
{
    const int TERRAIN_YOFFSET = 81;
    int offset = (((cam->getHeading() * 16) + ((cam->getPos().getX() + cam->getPos().getY()) / 100)) % (m_texture->getWidth() / 3));
    for (unsigned int i = 0; i < m_vertices.size(); i++)
    {
        Vector2D v = m_vertices[i].toFirstPerson(w, h, cam->getHeading());
        m_xCoords[i] = v.getX();
        m_yCoords[i] = v.getY();
    }
    MediaToolkit::getInstance()->getVideo()->fillPolygon(m_xCoords, m_yCoords, m_vertices.size(), m_texture->getPixels(),
            offset - x, TERRAIN_YOFFSET - y - h + TERRAIN_HEIGHT, m_texture->getWidth());
}

void PatternPolygonObject::drawTopDown()
{
}
