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

#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "geometry.h"

const int NORTH = 0;
const int EAST  = ANGLE_SIZE / 4;
const int SOUTH = ANGLE_SIZE / 2;
const int WEST  = 3 * ANGLE_SIZE / 4;

const int TURN_SIZE  = 2;
const int TURN_LEFT  = -1 * TURN_SIZE;
const int TURN_RIGHT = +1 * TURN_SIZE;

class Orientation
{
private:
    Angle m_heading;
public:
    Orientation ( const int head );
    virtual ~Orientation();
    const Angle & getAngle() const;
    int getHeading() const;
    void setHeading ( const int head );
    double getCos() const;
    double getSin() const;
    void adjustHeading ( const int delta );
};

#endif
