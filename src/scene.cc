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

#include "mediatoolkit.h"
#include "scene.h"

Scene::Scene(Image *horizon, Image *terrain)
    : m_video(MediaToolkit::getInstance()->getVideo())
    , m_horizonTexture(horizon)
    , m_terrainTexture(terrain)
    , m_objects()
    , m_zBuffer()
{
}

Scene::~Scene()
{
    for (std::multimap<const Vector2D, GenericObject *>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        delete it->second;
    }
    m_objects.clear();
    m_zBuffer.clear();
    delete m_horizonTexture;
    delete m_terrainTexture;
}

void Scene::addObject(const Vector2D &cell, GenericObject *obj)
{
    m_objects.insert(std::pair<const Vector2D, GenericObject *>(cell, obj));
}

void Scene::fillZBuffer(Camera *cam)
{
    m_zBuffer.clear();
    Vector2D cell = cam->getPosition().getCell();
    Vector2D pos = cam->getPos();
    Angle angle = cam->getAngle();
    for (std::multimap<const Vector2D, GenericObject *>::iterator it = m_objects.lower_bound(cell); it != m_objects.upper_bound(cell); ++it)
    {
        it->second->calculateRelativePosition(pos);
        unsigned int distance;
        if (it->second->isInView(angle, distance))
        {
            m_zBuffer.insert(std::pair<int, GenericObject *>(distance, it->second));
        }
    }
}

void Scene::drawHorizon(const int x, const int y, const int w, const int, Camera *cam)
{
    const int HORIZON_TOP_SIZE = 34;
    m_video->fillRect(x, y, w, HORIZON_TOP_SIZE, m_horizonTexture->getPixel(0, 0));
    m_video->fillRect(x, y + HORIZON_TOP_SIZE, w, m_horizonTexture->getHeight(), m_horizonTexture->getPixels(),
                    (cam->getHeading() << 2) - x, -y - HORIZON_TOP_SIZE, m_horizonTexture->getWidth());
}

void Scene::drawGround(const int x, const int y, const int w, const int h, Camera *cam)
{
    const int TERRAIN_YOFFSET = 81;
    int offset = (((cam->getHeading() * 16) + ((cam->getPos().getX() + cam->getPos().getY()) / 100)) % (m_terrainTexture->getWidth() / 3));
    m_video->fillRect(x, y + h - TERRAIN_HEIGHT, w, TERRAIN_HEIGHT, m_terrainTexture->getPixels(),
                    offset - x, TERRAIN_YOFFSET - y - h + TERRAIN_HEIGHT, m_terrainTexture->getWidth());
}

void Scene::drawZBuffer(const int x, const int y, const int w, const int h, Camera *cam)
{
    for (std::multimap<const unsigned int, GenericObject *>::reverse_iterator it = m_zBuffer.rbegin(); it != m_zBuffer.rend(); it++)
    {
        it->second->drawFirstPerson(x, y, w, h, cam);
    }
}

void Scene::drawFirstPerson(const int x, const int y, const int w, const int h, Camera *cam)
{
    fillZBuffer(cam);
    drawGround(x, y, w, h, cam);
    drawHorizon(x, y, w, h, cam);
    drawZBuffer(x, y, w, h, cam);
}

void Scene::drawTopDown()
{
}
