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

#ifndef POSITION_H
#define POSITION_H

#include "geometry.h"

const int MOVE_SIZE     = 400;
const int MOVE_FORWARD  = +1 * MOVE_SIZE;
const int MOVE_BACKWARD = -1 * MOVE_SIZE;

class Position
{
private:
    Vector2D m_pos;
    Vector2D m_cell;
public:
    Position ( const Vector2D &p );
    Position ( const Vector2D &p, const Vector2D &c );
    virtual ~Position();
    const Vector2D & getCell() const;
    const Vector2D & getPos() const;
    void setPos ( const Vector2D &p );
    void adjust ( const Vector2D &delta );
    void adjust ( const int deltaX, const int deltaY );
};

#endif
