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

#ifndef CAMERA_H
#define CAMERA_H

#include "orientation.h"
#include "position.h"
#include "subject.h"

class Camera
    : public Subject
{
private:
    Position m_position;
    Orientation m_orientation;
public:
    Camera ( const Vector2D &p, const int heading );
    ~Camera();
    const Position & getPosition() const;
    const Vector2D & getPos() const;
    void setPosition ( const Vector2D &p );
    const Orientation & getOrientation() const;
    const Angle & getAngle() const;
    int getHeading() const;
    void setHeading ( const int heading );
    void move ( const int delta );
    void turn ( const int delta );
};

#endif
