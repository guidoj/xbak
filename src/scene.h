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

#ifndef SCENE_H
#define SCENE_H

#include <map>

#include "genericobject.h"
#include "image.h"
#include "video.h"

class Scene
{
private:
    Video *m_video;
    Image *m_horizonTexture;
    Image *m_terrainTexture;
    std::multimap<const Vector2D, GenericObject *> m_objects;
    std::multimap<const unsigned int, GenericObject *> m_zBuffer;
    void fillZBuffer ( Camera *cam );
    void drawHorizon ( const int x, const int y, const int w, const int h, Camera *cam );
    void drawGround ( const int x, const int y, const int w, const int h, Camera *cam );
    void drawZBuffer ( const int x, const int y, const int w, const int h, Camera *cam );
public:
    Scene ( Image *horizon, Image *terrain );
    virtual ~Scene();
    void addObject ( const Vector2D &cell, GenericObject *obj );
    void drawFirstPerson ( const int x, const int y, const int w, const int h, Camera *cam );
    void drawTopDown();
};

#endif
