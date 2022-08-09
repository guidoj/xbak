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

#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

#include "scene.h"
#include "zone.h"

class SceneFactory
{
private:
    Zone &m_zone;
    void addFixedObjects ( Scene* scene );
    void addTiledObjects ( Scene* scene, unsigned int x, unsigned int y, Image *terrainTexture );
public:
    SceneFactory( Zone &z );
    virtual ~SceneFactory();
    Scene * createScene();
};

#endif
