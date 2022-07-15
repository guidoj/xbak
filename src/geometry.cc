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

#include "geometry.h"

bool  Angle::m_initialized = false;
double Angle::m_cosTbl[ANGLE_SIZE];
double Angle::m_sinTbl[ANGLE_SIZE];
double Angle::m_tanTbl[ANGLE_SIZE];

Angle::Angle ( const int a )
    : m_angle(a & ANGLE_MASK)
{
    if (!m_initialized)
    {
        for (unsigned int i = 0; i < ANGLE_SIZE; i++)
        {
            m_cosTbl[i] = cos((double)i * PI2 / (double)ANGLE_SIZE);
            m_sinTbl[i] = sin((double)i * PI2 / (double)ANGLE_SIZE);
            m_tanTbl[i] = tan((double)i * PI2 / (double)ANGLE_SIZE);
        }
        m_initialized = true;
    }
}

Angle::~Angle()
{
}

int Angle::get() const
{
    return m_angle;
}

void Angle::set ( const int a )
{
    m_angle = a & ANGLE_MASK;
}

double Angle::getCos() const
{
    return m_cosTbl[m_angle];
}

double Angle::getSin() const
{
    return m_sinTbl[m_angle];
}

double Angle::getTan() const
{
    return m_tanTbl[m_angle];
}

Angle& Angle::operator= ( const Angle &a )
{
    m_angle = a.m_angle;
    return *this;
}

Angle& Angle::operator+= ( const Angle &a )
{
    m_angle = (m_angle + a.m_angle) & ANGLE_MASK;
    return *this;
}

Angle& Angle::operator-= ( const Angle &a )
{
    m_angle = (m_angle - a.m_angle) & ANGLE_MASK;
    return *this;
}

Angle Angle::operator+ ( const Angle &a )
{
    return Angle(m_angle + a.m_angle);
}

Angle Angle::operator- ( const Angle &a )
{
    return Angle(m_angle - a.m_angle);
}

bool Angle::operator== ( const Angle &a ) const
{
    return m_angle == a.m_angle;
}

bool Angle::operator!= ( const Angle &a ) const
{
    return m_angle != a.m_angle;
}

bool Angle::operator< ( const Angle &a ) const
{
    return m_angle < a.m_angle;
}

bool Angle::operator> ( const Angle &a ) const
{
    return m_angle > a.m_angle;
}

bool Angle::operator<= ( const Angle &a ) const
{
    return m_angle <= a.m_angle;
}

bool Angle::operator>= ( const Angle &a ) const
{
    return m_angle >= a.m_angle;
}

Vector2D::Vector2D()
    : m_x(0)
    , m_y(0)
{
}

Vector2D::Vector2D(const int x, const int y)
    : m_x(x)
    , m_y(y)
{
}

Vector2D::Vector2D(const Vector2D &p)
    : m_x(p.m_x)
    , m_y(p.m_y)
{
}

Vector2D::~Vector2D()
{
}

Vector2D& Vector2D::operator=(const Vector2D &p)
{
    m_x = p.m_x;
    m_y = p.m_y;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D &p)
{
    m_x += p.m_x;
    m_y += p.m_y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D &p)
{
    m_x -= p.m_x;
    m_y -= p.m_y;
    return *this;
}

Vector2D& Vector2D::operator*=(const int f)
{
    m_x *= f;
    m_y *= f;
    return *this;
}

Vector2D& Vector2D::operator/=(const int f)
{
    m_x /= f;
    m_y /= f;
    return *this;
}

Vector2D& Vector2D::operator*=(const double f)
{
    m_x = (int)((double)m_x * f);
    m_y = (int)((double)m_y * f);
    return *this;
}

Vector2D& Vector2D::operator/=(const double f)
{
    m_x = (int)((double)m_x / f);
    m_y = (int)((double)m_y / f);
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D &p)
{
    return Vector2D(m_x + p.m_x, m_y + p.m_y);
}

Vector2D Vector2D::operator-(const Vector2D &p)
{
    return Vector2D(m_x - p.m_x, m_y - p.m_y);
}

Vector2D Vector2D::operator*(const int f)
{
    return Vector2D(m_x * f, m_y * f);
}

Vector2D Vector2D::operator/(const int f)
{
    return Vector2D(m_x / f, m_y / f);
}

Vector2D Vector2D::operator*(const double f)
{
    return Vector2D((int)((double)m_x * f), (int)((double)m_y * f));
}

Vector2D Vector2D::operator/(const double f)
{
    return Vector2D((int)((double)m_x / f), (int)((double)m_y / f));
}

bool Vector2D::operator==(const Vector2D &p) const
{
    return (m_x == p.m_x) && (m_y == p.m_y);
}

bool Vector2D::operator!=(const Vector2D &p) const
{
    return (m_x != p.m_x) || (m_y != p.m_y);
}

bool Vector2D::operator<(const Vector2D &p) const
{
    return ((m_x < p.m_x) && (m_y <= p.m_y)) ||
           ((m_y < p.m_y) && (m_x <= p.m_x));
}

bool Vector2D::operator>(const Vector2D &p) const
{
    return ((m_x > p.m_x) && (m_y >= p.m_y)) ||
           ((m_y > p.m_y) && (m_x >= p.m_x));
}

bool Vector2D::operator<=(const Vector2D &p) const
{
    return (m_x <= p.m_x) && (m_y <= p.m_y);
}

bool Vector2D::operator>=(const Vector2D &p) const
{
    return (m_x >= p.m_x) && (m_y >= p.m_y);
}

int Vector2D::getX() const
{
    return m_x;
}

int Vector2D::getY() const
{
    return m_y;
}

void Vector2D::setX(const int x)
{
    m_x = x;
}

void Vector2D::setY(const int y)
{
    m_y = y;
}

unsigned int Vector2D::getRho() const
{
    return (unsigned int)sqrt(((double)m_x * (double)m_x) + ((double)m_y * (double)m_y));
}

int Vector2D::getTheta() const
{
    if (m_x == 0)
    {
        if (m_y >= 0)
        {
            return ANGLE_SIZE / 4;
        }
        else
        {
            return - ANGLE_SIZE / 4;
        }
    }
    else
    {
        int angle = (int)((atan((double)m_y / (double)m_x) / PI2) * (double)ANGLE_SIZE);
        if (m_x > 0)
        {
            return angle & ANGLE_MASK;
        }
        else
        {
            return (angle + ANGLE_SIZE / 2) & ANGLE_MASK;
        }
    }
}


Vector3D::Vector3D()
    : m_x(0)
    , m_y(0)
    , m_z(0)
{
}

Vector3D::Vector3D(const int x, const int y, const int z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{
}

Vector3D::Vector3D(const Vector3D &p)
    : m_x(p.m_x)
    , m_y(p.m_y)
    , m_z(p.m_z)
{
}

Vector3D::Vector3D(const Vector2D &p)
    : m_x(p.getX())
    , m_y(p.getY())
    , m_z(0)
{
}

Vector3D::~Vector3D()
{
}

Vector3D& Vector3D::operator=(const Vector3D &p)
{
    m_x = p.m_x;
    m_y = p.m_y;
    m_z = p.m_z;
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D &p)
{
    m_x += p.m_x;
    m_y += p.m_y;
    m_z += p.m_z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D &p)
{
    m_x -= p.m_x;
    m_y -= p.m_y;
    m_z -= p.m_z;
    return *this;
}

Vector3D& Vector3D::operator=(const Vector2D &p)
{
    m_x = p.getX();
    m_y = p.getY();
    m_z = 0;
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector2D &p)
{
    m_x += p.getX();
    m_y += p.getY();
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector2D &p)
{
    m_x -= p.getX();
    m_y -= p.getY();
    return *this;
}

Vector3D& Vector3D::operator*=(const int f)
{
    m_x *= f;
    m_y *= f;
    m_z *= f;
    return *this;
}

Vector3D& Vector3D::operator/=(const int f)
{
    m_x /= f;
    m_y /= f;
    m_z /= f;
    return *this;
}

Vector3D& Vector3D::operator*=(const double f)
{
    m_x = (int)((double)m_x * f);
    m_y = (int)((double)m_y * f);
    m_z = (int)((double)m_z * f);
    return *this;
}

Vector3D& Vector3D::operator/=(const double f)
{
    m_x = (int)((double)m_x / f);
    m_y = (int)((double)m_y / f);
    m_z = (int)((double)m_z / f);
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D &p)
{
    return Vector3D(m_x + p.m_x, m_y + p.m_y, m_z + p.m_z);
}

Vector3D Vector3D::operator-(const Vector3D &p)
{
    return Vector3D(m_x - p.m_x, m_y - p.m_y, m_z - p.m_z);
}

Vector3D Vector3D::operator+(const Vector2D &p)
{
    return Vector3D(m_x + p.getX(), m_y + p.getY(), m_z);
}

Vector3D Vector3D::operator-(const Vector2D &p)
{
    return Vector3D(m_x - p.getX(), m_y - p.getY(), m_z);
}

Vector3D Vector3D::operator*(const int f)
{
    return Vector3D(m_x * f, m_y * f, m_z * f);
}

Vector3D Vector3D::operator/(const int f)
{
    return Vector3D(m_x / f, m_y / f, m_z / f);
}

Vector3D Vector3D::operator*(const double f)
{
    return Vector3D((int)((double)m_x * f), (int)((double)m_y * f), (int)((double)m_z * f));
}

Vector3D Vector3D::operator/(const double f)
{
    return Vector3D((int)((double)m_x / f), (int)((double)m_y / f), (int)((double)m_z / f));
}

bool Vector3D::operator==(const Vector3D &p) const
{
    return (m_x == p.m_x) && (m_y == p.m_y) && (m_z == p.m_z);
}

bool Vector3D::operator!=(const Vector3D &p) const
{
    return (m_x != p.m_x) || (m_y != p.m_y) || (m_z != p.m_z);
}

bool Vector3D::operator<(const Vector3D &p) const
{
    return ((m_x < p.m_x) && (m_y <= p.m_y) && (m_z <= p.m_z)) ||
           ((m_y < p.m_y) && (m_z <= p.m_z) && (m_x <= p.m_x)) ||
           ((m_z < p.m_z) && (m_x <= p.m_x) && (m_y <= p.m_y));
}

bool Vector3D::operator>(const Vector3D &p) const
{
    return ((m_x > p.m_x) && (m_y >= p.m_y) && (m_z >= p.m_z)) ||
           ((m_y > p.m_y) && (m_z >= p.m_z) && (m_x >= p.m_x)) ||
           ((m_z > p.m_z) && (m_x >= p.m_x) && (m_y >= p.m_y));
}

bool Vector3D::operator<=(const Vector3D &p) const
{
    return (m_x <= p.m_x) && (m_y <= p.m_y) && (m_z <= p.m_z);
}

bool Vector3D::operator>=(const Vector3D &p) const
{
    return (m_x >= p.m_x) && (m_y >= p.m_y) && (m_z >= p.m_z);
}

int Vector3D::getX() const
{
    return m_x;
}

int Vector3D::getY() const
{
    return m_y;
}

int Vector3D::getZ() const
{
    return m_z;
}

void Vector3D::setX(const int x)
{
    m_x = x;
}

void Vector3D::setY(const int y)
{
    m_y = y;
}

void Vector3D::setZ(const int z)
{
    m_z = z;
}

unsigned int Vector3D::getRho() const
{
    return (unsigned int)sqrt(((double)m_x * (double)m_x) + ((double)m_y * (double)m_y) + ((double)m_z * (double)m_z));
}

int Vector3D::getTheta() const
{
    if (m_x == 0)
    {
        if (m_y >= 0)
        {
            return ANGLE_SIZE / 4;
        }
        else
        {
            return - ANGLE_SIZE / 4;
        }
    }
    else
    {
        int angle = (int)((atan((double)m_y / (double)m_x) / PI2) * (double)ANGLE_SIZE);
        if (m_x > 0)
        {
            return angle & ANGLE_MASK;
        }
        else
        {
            return (angle + ANGLE_SIZE / 2) & ANGLE_MASK;
        }
    }
}


Rectangle::Rectangle(const int x, const int y, const int w, const int h)
    : m_x(x)
    , m_y(y)
    , m_width(w)
    , m_height(h)
{
}

Rectangle::Rectangle(const Rectangle &r)
    : m_x(r.m_x)
    , m_y(r.m_y)
    , m_width(r.m_width)
    , m_height(r.m_height)
{
}

Rectangle::~Rectangle()
{
}

Rectangle& Rectangle::operator=(const Rectangle &r)
{
    m_x = r.m_x;
    m_y = r.m_y;
    m_width = r.m_width;
    m_height = r.m_height;
    return *this;
}

bool Rectangle::operator==(const Rectangle &r)
{
    return (m_x == r.m_x) && (m_y == r.m_y) && (m_width == r.m_width) && (m_height == r.m_height);
}

bool Rectangle::operator!=(const Rectangle &r)
{
    return (m_x != r.m_x) || (m_y != r.m_y) || (m_width != r.m_width) || (m_height != r.m_height);
}

bool Rectangle::operator<(const Rectangle &r)
{
    return (m_x < r.m_x) ||
           ((m_x == r.m_x) && (m_y < r.m_y)) ||
           ((m_x == r.m_x) && (m_y == r.m_y) && ((m_width * m_height) < (r.m_width * r.m_height)));
}

bool Rectangle::operator>(const Rectangle &r)
{
    return (m_x > r.m_x) ||
           ((m_x == r.m_x) && (m_y > r.m_y)) ||
           ((m_x == r.m_x) && (m_y == r.m_y) && ((m_width * m_height) > (r.m_width * r.m_height)));
}

bool Rectangle::operator<=(const Rectangle &r)
{
    return (m_x <= r.m_x) ||
           ((m_x == r.m_x) && (m_y <= r.m_y)) ||
           ((m_x == r.m_x) && (m_y == r.m_y) && ((m_width * m_height) <= (r.m_width * r.m_height)));
}

bool Rectangle::operator>=(const Rectangle &r)
{
    return (m_x >= r.m_x) ||
           ((m_x == r.m_x) && (m_y >= r.m_y)) ||
           ((m_x == r.m_x) && (m_y == r.m_y) && ((m_width * m_height) >= (r.m_width * r.m_height)));
}

int Rectangle::getXPos() const
{
    return m_x;
}

int Rectangle::getYPos() const
{
    return m_y;
}

int Rectangle::getXCenter() const
{
    return m_x + m_width / 2;
}

int Rectangle::getYCenter() const
{
    return m_y + m_height / 2;
}

int Rectangle::getWidth() const
{
    return m_width;
}

int Rectangle::getHeight() const
{
    return m_height;
}

void Rectangle::setXPos(const int x)
{
    m_x = x;
}

void Rectangle::setYPos(const int y)
{
    m_y = y;
}

void Rectangle::setWidth(const int w)
{
    m_width = w;
}

void Rectangle::setHeight(const int h)
{
    m_height = h;
}

bool Rectangle::isInside(const Vector2D &p) const
{
    return ((m_x <= p.getX()) && (p.getX() < m_x + m_width) &&
            (m_y <= p.getY()) && (p.getY() < m_y + m_height));
}
