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

#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H

#include "game.h"
#include "gamedata.h"

class GameResource
    : public GameData
{
private:
    Game *m_game;
    unsigned int m_zone;
    unsigned int m_xLoc;
    unsigned int m_yLoc;
public:
    GameResource();
    virtual ~GameResource();
    Game * getGame();
    void setGame ( Game *g );
    unsigned int getZone() const;
    void setZone ( const unsigned int z );
    unsigned int getXLoc() const;
    void setXLoc ( const unsigned int x );
    unsigned int getYLoc() const;
    void setYLoc ( const unsigned int y );
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif
