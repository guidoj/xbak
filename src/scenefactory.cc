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

#include "patternpolygonobject.h"
#include "scenefactory.h"
#include "solidpolygonobject.h"
#include "spriteobject.h"

SceneFactory::SceneFactory(Zone &z)
    : m_zone(z)
{
}

SceneFactory::~SceneFactory()
{
}

void SceneFactory::addFixedObjects(Scene* scene)
{
    TableResource *table = m_zone.getTable();
    if (scene && table)
    {
        for (unsigned int i = 0; i < table->getMapSize(); i++)
        {
            DatInfo *dat = table->getDatItem(i);
            switch (dat->entityType)
            {
            case ET_EXTERIOR:
            {
                /*                        PatternPolygonObject *terrObj = new PatternPolygonObject();
                                        for (unsigned j = 0; j < dat->vertices.size(); j++)
                                        {
                                            terrObj->AddVertex(Vertex(*(dat->vertices[j])));
                                        }
                                        scene->AddObject(Vector2D(x, y), terrObj);*/
            }
            break;
            default:
                break;
            }
        }
    }
}

void SceneFactory::addTiledObjects(Scene* scene, unsigned int x, unsigned int y, Image* /*terrainTexture*/)
{
    TableResource *table = m_zone.getTable();
    TileWorldResource *tile = m_zone.getTile(x, y);
    if (scene && table && tile)
    {
        for (unsigned int i = 0; i < tile->getSize(); i++)
        {
            TileWorldItem item = tile->getItem(i);
            DatInfo *dat = table->getDatItem(item.type);
            switch (dat->entityType)
            {
            case ET_TERRAIN:
                // terrain tiles are not required and will only slow things down
                break;
            case ET_HILL:
            {
                SolidPolygonObject *spObj = new SolidPolygonObject(Vector2D(item.xloc + dat->max.getX() / 2, item.yloc), 218);
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, dat->max.getZ() - dat->min.getZ())));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->max.getX(), dat->max.getY(), 0)));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->max.getX(), dat->min.getY(), 0)));
                scene->addObject(Vector2D(x, y), spObj);

                spObj = new SolidPolygonObject(Vector2D(item.xloc, item.yloc + dat->min.getY() / 2), 219);
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, dat->max.getZ() - dat->min.getZ())));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->max.getX(), dat->min.getY(), 0)));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->min.getX(), dat->min.getY(), 0)));
                scene->addObject(Vector2D(x, y), spObj);

                spObj = new SolidPolygonObject(Vector2D(item.xloc + dat->min.getX() / 2, item.yloc), 220);
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, dat->max.getZ() - dat->min.getZ())));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->min.getX(), dat->min.getY(), 0)));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->min.getX(), dat->max.getY(), 0)));
                scene->addObject(Vector2D(x, y), spObj);

                spObj = new SolidPolygonObject(Vector2D(item.xloc, item.yloc + dat->max.getY() / 2), 221);
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, dat->max.getZ() - dat->min.getZ())));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->min.getX(), dat->max.getY(), 0)));
                spObj->addVertex(Vertex(Vector3D(item.xloc, item.yloc, 0) + Vector3D(dat->max.getX(), dat->max.getY(), 0)));
                scene->addObject(Vector2D(x, y), spObj);
            }
            break;
            case ET_TREE:
            case ET_TOMBSTONE:
            case ET_SIGN:
            case ET_DEADBODY2:
            case ET_DIRTPILE:
            case ET_FIRE:
            case ET_FERN:
            case ET_ROCKPILE:
            case ET_BUSH1:
            case ET_BUSH2:
            case ET_BUSH3:
            case ET_SLAB:
            case ET_STUMP:
            case ET_WELL:
            case ET_ENGINE:
            case ET_SCARECROW:
            case ET_TRAP:
            case ET_COLUMN:
            case ET_BAG:
            case ET_LADDER:
                scene->addObject(Vector2D(x, y), new SpriteObject(Vector2D(item.xloc, item.yloc), m_zone.getSprite(dat->sprite)));
                break;
            default:
                break;
            }
        }
    }
}

Scene * SceneFactory::createScene()
{
    std::vector<Image *> horizonImages;
    horizonImages.push_back(m_zone.getHorizon(3));
    horizonImages.push_back(m_zone.getHorizon(0));
    horizonImages.push_back(m_zone.getHorizon(1));
    horizonImages.push_back(m_zone.getHorizon(2));
    horizonImages.push_back(m_zone.getHorizon(3));
    horizonImages.push_back(m_zone.getHorizon(0));
    Image *horizonTexture = new Image(m_zone.getHorizon(0)->getWidth() * horizonImages.size(), m_zone.getHorizon(0)->getHeight(), horizonImages);
    std::vector<Image *> terrainImages;
    Image terrain1(m_zone.getTerrain()->getWidth(), m_zone.getTerrain()->getHeight() - 2, m_zone.getTerrain()->getPixels());
    terrainImages.push_back(&terrain1);
    Image terrain2(m_zone.getTerrain()->getWidth(), m_zone.getTerrain()->getHeight() - 2, m_zone.getTerrain()->getPixels() + m_zone.getTerrain()->getWidth());
    terrainImages.push_back(&terrain2);
    Image terrain3(m_zone.getTerrain()->getWidth(), m_zone.getTerrain()->getHeight() - 2, m_zone.getTerrain()->getPixels() + 2 * m_zone.getTerrain()->getWidth());
    terrainImages.push_back(&terrain3);
    Image *terrainTexture = new Image(m_zone.getTerrain()->getWidth() * terrainImages.size(), m_zone.getTerrain()->getHeight() - 2, terrainImages);
    Scene *scene = new Scene(horizonTexture, terrainTexture);
    addFixedObjects(scene);
    for (unsigned int y = 1; y <= MAX_TILES; y++)
    {
        for (unsigned int x = 1; x <= MAX_TILES; x++)
        {
            addTiledObjects(scene, x, y, terrainTexture);
        }
    }
    return scene;
}
