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

#include "polygonobject.h"

PolygonObject::PolygonObject(const Vector2D& p)
    : GenericObject(p)
    , m_vertices()
    , m_xCoords(0)
    , m_yCoords(0)
{
}

PolygonObject::~PolygonObject()
{
    if (m_xCoords != 0)
    {
        delete m_xCoords;
    }
    if (m_yCoords != 0)
    {
        delete m_yCoords;
    }
    m_vertices.clear();
}

void PolygonObject::addVertex(const Vertex& v)
{
    m_vertices.push_back(v);
    if (m_xCoords != 0)
    {
        delete m_xCoords;
    }
    if (m_yCoords != 0)
    {
        delete m_yCoords;
    }
    m_xCoords = new int[m_vertices.size()];
    m_yCoords = new int[m_vertices.size()];
}

Vertex& PolygonObject::getVertex(const unsigned int i)
{
    return m_vertices[i];
}

unsigned int PolygonObject::getNumVertices()
{
    return m_vertices.size();
}

void PolygonObject::calculateRelativePosition(const Vector2D & p)
{
    m_pos.calculateRelativePosition(p);
    for (std::vector<Vertex>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        it->calculateRelativePosition(p);
    }
}

bool PolygonObject::isInView(const Angle & heading, unsigned int & distance)
{
    if (m_pos.isInView(heading))
    {
        distance = m_pos.getDistance();
        return true;
    }
    for (std::vector<Vertex>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        if (it->isInView(heading))
        {
            distance = it->getDistance();
            return true;
        }
    }
    return false;
}
