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
#include "solidpolygonobject.h"

SolidPolygonObject::SolidPolygonObject(const Vector2D& p, const unsigned int c)
    : PolygonObject(p)
    , m_color(c)
{
}

SolidPolygonObject::~SolidPolygonObject()
{
}

void SolidPolygonObject::drawFirstPerson(const int x, const int y, const int w, const int h, Camera *cam)
{
    for (unsigned int i = 0; i < m_vertices.size(); i++)
    {
        Vector2D v = m_vertices[i].toFirstPerson(w, h, cam->getAngle());
        m_xCoords[i] = x + v.getX();
        m_yCoords[i] = y + v.getY();
    }
    MediaToolkit::getInstance()->getVideo()->fillPolygon(m_xCoords, m_yCoords, m_vertices.size(), m_color);
}

void SolidPolygonObject::drawTopDown()
{
}
