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

#include "orientation.h"
#include "position.h"
#include "tileworldresource.h"

Position::Position(const Vector2D &p)
    : m_pos(p)
    , m_cell(p.getX() / TILE_SIZE, p.getY() / TILE_SIZE)
{}

Position::Position(const Vector2D &p, const Vector2D &c)
    : m_pos(p)
    , m_cell(c)
{}

Position::~Position()
{
}

const Vector2D & Position::getCell() const
{
    return m_cell;
}

const Vector2D & Position::getPos() const
{
    return m_pos;
}

void Position::setPos(const Vector2D &p)
{
    m_pos = p;
    m_cell = m_pos / (int)TILE_SIZE;
}

void Position::adjust(const Vector2D &delta)
{
    m_pos += delta;
    m_cell = m_pos / (int)TILE_SIZE;
}

void Position::adjust(const int deltaX, const int deltaY)
{
    m_pos += Vector2D(deltaX, deltaY);
    m_cell = m_pos / (int)TILE_SIZE;
}
