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

#include "camera.h"

Camera::Camera(const Vector2D &p, const int heading)
    : m_position(p)
    , m_orientation(heading)
{
}

Camera::~Camera()
{
}

const Position & Camera::getPosition() const
{
    return m_position;
}

const Vector2D & Camera::getPos() const
{
    return m_position.getPos();
}

void Camera::setPosition(const Vector2D &p)
{
    m_position.setPos(p);
    notify();
}

const Orientation & Camera::getOrientation() const
{
    return m_orientation;
}

const Angle & Camera::getAngle() const
{
    return m_orientation.getAngle();
}

int Camera::getHeading() const
{
    return m_orientation.getHeading();
}

void Camera::setHeading(const int heading)
{
    m_orientation.setHeading(heading);
    notify();
}

void Camera::move(const int delta)
{
    m_position.adjust((int)((double)delta * m_orientation.getSin()),
                    (int)((double)delta * m_orientation.getCos()));
    notify();
}

void Camera::turn(const int delta)
{
    m_orientation.adjustHeading(delta);
    notify();
}
