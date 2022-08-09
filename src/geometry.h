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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double PI  = M_PI;
const double PI2 = M_PI + M_PI;

const unsigned int ANGLE_BITS = 8;
const unsigned int ANGLE_SIZE = 1 << ANGLE_BITS;
const unsigned int ANGLE_MASK = ANGLE_SIZE - 1;

class Angle
{
private:
    int m_angle;
    static bool m_initialized;
    static double m_cosTbl[ANGLE_SIZE];
    static double m_sinTbl[ANGLE_SIZE];
    static double m_tanTbl[ANGLE_SIZE];
public:
    Angle ( const int a );
    Angle ( const Angle &a );
    virtual ~Angle();
    int get() const;
    void set ( const int a );
    double getCos() const;
    double getSin() const;
    double getTan() const;
    Angle& operator= ( const Angle &a );
    Angle& operator+= ( const Angle &a );
    Angle& operator-= ( const Angle &a );
    Angle operator+ ( const Angle &a );
    Angle operator- ( const Angle &a );
    bool operator== ( const Angle &a ) const;
    bool operator!= ( const Angle &a ) const;
    bool operator< ( const Angle &a ) const;
    bool operator> ( const Angle &a ) const;
    bool operator<= ( const Angle &a ) const;
    bool operator>= ( const Angle &a ) const;
};

class Vector2D
{
private:
    int m_x;
    int m_y;
public:
    Vector2D();
    Vector2D ( const int x, const int y );
    Vector2D ( const Vector2D &p );
    virtual ~Vector2D();
    Vector2D& operator= ( const Vector2D &p );
    Vector2D& operator+= ( const Vector2D &p );
    Vector2D& operator-= ( const Vector2D &p );
    Vector2D& operator*= ( const int f );
    Vector2D& operator/= ( const int f );
    Vector2D& operator*= ( const double f );
    Vector2D& operator/= ( const double f );
    Vector2D operator+ ( const Vector2D &p );
    Vector2D operator- ( const Vector2D &p );
    Vector2D operator* ( const int f );
    Vector2D operator/ ( const int f );
    Vector2D operator* ( const double f );
    Vector2D operator/ ( const double f );
    bool operator== ( const Vector2D &p ) const;
    bool operator!= ( const Vector2D &p ) const;
    bool operator< ( const Vector2D &p ) const;
    bool operator> ( const Vector2D &p ) const;
    bool operator<= ( const Vector2D &p ) const;
    bool operator>= ( const Vector2D &p ) const;
    int getX() const;
    int getY() const;
    void setX ( const int x );
    void setY ( const int y );
    unsigned int getRho() const;
    int getTheta() const;
};

class Vector3D
{
private:
    int m_x;
    int m_y;
    int m_z;
public:
    Vector3D();
    Vector3D ( const int x, const int y, const int z );
    Vector3D ( const Vector3D &p );
    Vector3D ( const Vector2D &p );
    virtual ~Vector3D();
    Vector3D& operator= ( const Vector3D &p );
    Vector3D& operator+= ( const Vector3D &p );
    Vector3D& operator-= ( const Vector3D &p );
    Vector3D& operator= ( const Vector2D &p );
    Vector3D& operator+= ( const Vector2D &p );
    Vector3D& operator-= ( const Vector2D &p );
    Vector3D& operator*= ( const int f );
    Vector3D& operator/= ( const int f );
    Vector3D& operator*= ( const double f );
    Vector3D& operator/= ( const double f );
    Vector3D operator+ ( const Vector3D &p );
    Vector3D operator- ( const Vector3D &p );
    Vector3D operator+ ( const Vector2D &p );
    Vector3D operator- ( const Vector2D &p );
    Vector3D operator* ( const int f );
    Vector3D operator/ ( const int f );
    Vector3D operator* ( const double f );
    Vector3D operator/ ( const double f );
    bool operator== ( const Vector3D &p ) const;
    bool operator!= ( const Vector3D &p ) const;
    bool operator< ( const Vector3D &p ) const;
    bool operator> ( const Vector3D &p ) const;
    bool operator<= ( const Vector3D &p ) const;
    bool operator>= ( const Vector3D &p ) const;
    int getX() const;
    int getY() const;
    int getZ() const;
    void setX ( const int x );
    void setY ( const int y );
    void setZ ( const int z );
    unsigned int getRho() const;
    int getTheta() const;
};

class Rectangle
{
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
public:
    Rectangle ( const int x, const int y, const int w, const int h );
    Rectangle ( const Rectangle &r );
    virtual ~Rectangle();
    Rectangle& operator= ( const Rectangle &r );
    bool operator== ( const Rectangle &r );
    bool operator!= ( const Rectangle &r );
    bool operator< ( const Rectangle &r );
    bool operator> ( const Rectangle &r );
    bool operator<= ( const Rectangle &r );
    bool operator>= ( const Rectangle &r );
    int getXPos() const;
    int getYPos() const;
    int getXCenter() const;
    int getYCenter() const;
    int getWidth() const;
    int getHeight() const;
    void setXPos ( const int x );
    void setYPos ( const int x );
    void setWidth ( const int w );
    void setHeight ( const int h );
    bool isInside ( const Vector2D &p ) const;
};

#endif
