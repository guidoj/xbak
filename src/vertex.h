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

#ifndef VERTEX_H
#define VERTEX_H

#include "geometry.h"

const unsigned int MAX_VIEW_DISTANCE = 32000;
const unsigned int MIN_VIEW_DISTANCE = 32;

const int ANGLE_OF_VIEW = 12;
const int ANGLE_VIEW_DISTANCE = MAX_VIEW_DISTANCE / 2;

const int TERRAIN_HEIGHT = 38;

class Vertex
{
protected:
    Vector3D m_pos;
    Vector3D m_relpos;
    Angle m_angle;
    unsigned int m_distance;
    double m_distanceFactor;
public:
    Vertex();
    Vertex ( const Vector3D &p );
    virtual ~Vertex();
    Vertex& operator= ( const Vertex &v );
    const Vector3D& getPosition() const;
    const Vector3D& getRelativePosition() const;
    int getAngle() const;
    unsigned int getDistance() const;
    double getDistanceFactor() const;
    Vector2D toFirstPerson ( int w, int h, const Angle & heading );
    Vector2D toTopDown ( int w, int h );
    void calculateRelativePosition ( const Vector2D &p );
    bool isInView ( const Angle & heading );
};

#endif
