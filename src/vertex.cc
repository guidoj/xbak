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

#include <cstdlib>

#include "orientation.h"
#include "vertex.h"

Vertex::Vertex()
    : m_pos(0, 0, 0)
    , m_relpos(0, 0, 0)
    , m_angle(0)
    , m_distance(0)
    , m_distanceFactor(1.0)
{
}

Vertex::Vertex(const Vector3D &p)
    : m_pos(p)
    , m_relpos(0, 0, 0)
    , m_angle(0)
    , m_distance(0)
    , m_distanceFactor(1.0)
{
}

Vertex::~Vertex()
{
}

Vertex& Vertex::operator= ( const Vertex &v )
{
    m_pos = v.m_pos;
    m_relpos = v.m_relpos;
    m_angle = v.m_angle;
    m_distance = v.m_distance;
    m_distanceFactor = v.m_distanceFactor;
    return *this;
}

const Vector3D& Vertex::getPosition() const
{
    return m_pos;
}

const Vector3D& Vertex::getRelativePosition() const
{
    return m_relpos;
}

int Vertex::getAngle() const
{
    return m_angle.get();
}

unsigned int Vertex::getDistance() const
{
    return m_distance;
}

double Vertex::getDistanceFactor() const
{
    return m_distanceFactor;
}

Vector2D Vertex::toFirstPerson(int w, int h, const Angle &heading)
{
    const int ANGLE_AOV = 2 * ANGLE_OF_VIEW + 1;
    int x = (int)((double)w * (double)(m_angle.get() - heading.get() + ANGLE_OF_VIEW - 1) / (double)ANGLE_AOV);
    int y = h - (int)((double)TERRAIN_HEIGHT * (1.0 - m_distanceFactor) + ((double)m_relpos.getZ() * (0.05 + 0.45 * m_distanceFactor)));
    return Vector2D(x, y);
}

Vector2D Vertex::toTopDown(int, int )
{
    // TODO
    return Vector2D(0, 0);
}

void Vertex::calculateRelativePosition(const Vector2D &p)
{
    m_relpos = m_pos - p;
    m_angle = Angle((ANGLE_SIZE / 4) - m_relpos.getTheta());
    m_distance = m_relpos.getRho();
    m_distanceFactor = 2.0 * ((double)MAX_VIEW_DISTANCE / ((double)MAX_VIEW_DISTANCE + (double)m_distance)) - 1.0;
    //distanceFactor = 1.0 - ((double)MAX_VIEW_DISTANCE / ((double)MAX_VIEW_DISTANCE + (double)distance));
}

bool Vertex::isInView(const Angle &heading)
{
    if (m_distance > MAX_VIEW_DISTANCE)
    {
        return false;
    }
    return (abs(m_angle.get() - heading.get()) <= ANGLE_OF_VIEW);
}
