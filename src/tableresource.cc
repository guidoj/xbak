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

#include "exception.h"
#include "tableresource.h"

DatInfo::DatInfo()
{
}

DatInfo::~DatInfo()
{
    for (std::vector<Vector3D*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
    {
        delete (*it);
    }
    vertices.clear();
}

GidInfo::GidInfo()
{
}

GidInfo::~GidInfo()
{
    for (std::vector<Vector2D*>::iterator it = textureCoords.begin(); it != textureCoords.end(); ++it)
    {
        delete (*it);
    }
    textureCoords.clear();
    for (std::vector<Vector2D*>::iterator it = otherCoords.begin(); it != otherCoords.end(); ++it)
    {
        delete (*it);
    }
    otherCoords.clear();
}

TableResource::TableResource()
    : TaggedResource()
    , m_mapItems()
{
}

TableResource::~TableResource()
{
    clear();
}

unsigned int
TableResource::getMapSize() const
{
    return m_mapItems.size();
}

std::string&
TableResource::getMapItem(const unsigned int i)
{
    return m_mapItems[i];
}

unsigned int
TableResource::getDatSize() const
{
    return m_datItems.size();
}

DatInfo*
TableResource::getDatItem(const unsigned int i)
{
    return m_datItems[i];
}

unsigned int
TableResource::getGidSize() const
{
    return m_gidItems.size();
}

GidInfo*
TableResource::getGidItem(const unsigned int i)
{
    return m_gidItems[i];
}

void
TableResource::clear()
{
    m_mapItems.clear();
    for (std::vector<DatInfo *>::iterator it = m_datItems.begin(); it != m_datItems.end(); ++it)
    {
        delete (*it);
    }
    m_datItems.clear();
    for (std::vector<GidInfo *>::iterator it = m_gidItems.begin(); it != m_gidItems.end(); ++it)
    {
        delete (*it);
    }
    m_gidItems.clear();
}

void
TableResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        split(buffer);
        FileBuffer *mapbuf;
        FileBuffer *appbuf;
        FileBuffer *gidbuf;
        FileBuffer *datbuf;
        if (!find(TAG_MAP, mapbuf) ||
                !find(TAG_APP, appbuf) ||
                !find(TAG_GID, gidbuf) ||
                !find(TAG_DAT, datbuf))
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        mapbuf->skip(2);
        unsigned int numMapItems = mapbuf->getUint16LE();
        unsigned int *mapOffset = new unsigned int [numMapItems];
        for (unsigned int i = 0; i < numMapItems; i++)
        {
            mapOffset[i] = mapbuf->getUint16LE();
        }
        mapbuf->skip(2);
        unsigned int mapDataStart = mapbuf->getBytesDone();
        for (unsigned int i = 0; i < numMapItems; i++)
        {
            mapbuf->seek(mapDataStart + mapOffset[i]);
            std::string item = mapbuf->getString();
            m_mapItems.push_back(item);
        }
        delete[] mapOffset;

        unsigned int numAppItems = appbuf->getUint16LE();
        unsigned int appDataSize = appbuf->getUint16LE();
        for (unsigned int i = 0; i< numAppItems; i++)
        {
            appbuf->skip(appDataSize);
        }

        unsigned int *gidOffset = new unsigned int [numMapItems];
        for (unsigned int i = 0; i < numMapItems; i++)
        {
            gidOffset[i] = (gidbuf->getUint16LE() & 0x000f) + (gidbuf->getUint16LE() << 4);
        }
        for (unsigned int i = 0; i < numMapItems; i++)
        {
            gidbuf->seek(gidOffset[i]);
            GidInfo *item = new GidInfo();
            item->xradius = gidbuf->getUint16LE();
            item->yradius = gidbuf->getUint16LE();
            bool more = gidbuf->getUint16LE() > 0;
            item->flags = gidbuf->getUint16LE();
            if (more)
            {
                gidbuf->skip(2);
                unsigned int n = gidbuf->getUint16LE();
                gidbuf->skip(2);
                for (unsigned int j = 0; j < n; j++)
                {
                    int u = gidbuf->getSint8();
                    int v = gidbuf->getSint8();
                    int x = gidbuf->getSint16LE();
                    int y = gidbuf->getSint16LE();
                    item->textureCoords.push_back(new Vector2D(u, v));
                    item->otherCoords.push_back(new Vector2D(x, y));
                }
            }
            m_gidItems.push_back(item);
        }
        delete[] gidOffset;

        unsigned int *datOffset = new unsigned int [numMapItems];
        for (unsigned int i = 0; i < numMapItems; i++)
        {
            datOffset[i] = (datbuf->getUint16LE() & 0x000f) + (datbuf->getUint16LE() << 4);
        }
        for (unsigned int i = 0; i < numMapItems; i++)
        {
            datbuf->seek(datOffset[i]);
            DatInfo *item = new DatInfo();
            item->entityFlags = datbuf->getUint8();
            item->entityType = datbuf->getUint8();
            item->terrainType = datbuf->getUint8();
            item->terrainClass = datbuf->getUint8();
            datbuf->skip(4);
            bool more = datbuf->getUint16LE() > 0;
            datbuf->skip(4);
            if (more)
            {
                if (!(item->entityFlags & EF_UNBOUNDED))
                {
                    item->min.setX(datbuf->getSint16LE());
                    item->min.setY(datbuf->getSint16LE());
                    item->min.setZ(datbuf->getSint16LE());
                    item->max.setX(datbuf->getSint16LE());
                    item->max.setY(datbuf->getSint16LE());
                    item->max.setZ(datbuf->getSint16LE());
                }
                datbuf->skip(2);
                unsigned int n = datbuf->getUint16LE();
                datbuf->skip(2);
                for (unsigned int j = 0; j < n; j++)
                {
                    datbuf->skip(14);
                }
                if (item->terrainType != TT_NULL)
                {
                    if (item->terrainClass == TC_FIELD)
                    {
                        item->pos.setX(datbuf->getSint16LE());
                        item->pos.setY(datbuf->getSint16LE());
                        item->pos.setZ(datbuf->getSint16LE());
                    }
                    datbuf->skip(6);
                    int x = datbuf->getSint16LE();
                    int y = datbuf->getSint16LE();
                    int z = datbuf->getSint16LE();
                    while ((item->min.getX() <= x) && (x <= item->max.getX()) &&
                            (item->min.getY() <= y) && (y <= item->max.getY()) &&
                            (item->min.getZ() <= z) && (z <= item->max.getZ()))
                    {
                        item->vertices.push_back(new Vector3D(x, y, z));
                        x = datbuf->getSint16LE();
                        y = datbuf->getSint16LE();
                        z = datbuf->getSint16LE();
                    }
                }
                if ((item->entityFlags & EF_UNBOUNDED) && (item->entityFlags & EF_2D_OBJECT) && (n == 1))
                {
                    datbuf->skip(2);
                    item->sprite = datbuf->getUint16LE();
                    datbuf->skip(4);
                }
                else
                {
                    item->sprite = (unsigned int) -1;
                }
            }
            m_datItems.push_back(item);
        }
        delete[] datOffset;

        clearTags();
    }
    catch (Exception &e)
    {
        e.print("TableResource::load");
        clearTags();
        throw;
    }
}

unsigned int
TableResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("TableResource::save");
        throw;
    }
}
