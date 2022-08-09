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

#ifndef ZONE_H
#define ZONE_H

#include "imageresource.h"
#include "tableresource.h"
#include "tileworldresource.h"

const unsigned int MAX_TILES = 32;

class Zone
{
private:
    ImageResource m_horizon;
    Image *m_terrain;
    Image *m_popUp;
    std::vector<Image *> m_sprites;
    std::map<const std::pair<unsigned int, unsigned int>, TileWorldResource *> m_tiles;
    TableResource *m_table;
public:
    Zone();
    virtual ~Zone();
    void clear();
    void load ( const unsigned int n );
    Image* getHorizon ( const unsigned int n );
    Image* getTerrain() const;
    Image* getPopUp() const;
    Image* getSprite ( const unsigned int n );
    TileWorldResource* getTile ( const unsigned int x, const unsigned int y );
    TableResource* getTable();
};

#endif
