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

#include <iomanip>
#include <sstream>

#include "exception.h"
#include "filemanager.h"
#include "screenresource.h"
#include "zone.h"

Zone::Zone()
    : m_horizon()
    , m_terrain ( 0 )
    , m_popUp ( 0 )
    , m_sprites()
    , m_tiles()
    , m_table ( 0 )
{}

Zone::~Zone()
{
    clear();
}

void
Zone::clear()
{
    for ( unsigned int i = 0; i < m_sprites.size(); i++ )
    {
        delete m_sprites[i];
    }
    m_sprites.clear();
    if ( m_terrain != 0 )
    {
        delete m_terrain;
    }
    if ( m_popUp != 0 )
    {
        delete m_popUp;
    }
    for ( std::map<const std::pair<unsigned int, unsigned int>, TileWorldResource *>::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
    {
        delete it->second;
    }
    m_tiles.clear();
    if ( m_table )
    {
        delete m_table;
    }
}

void
Zone::load ( const unsigned int n )
{
    try
    {
        clear();

        std::stringstream horizonStream;
        horizonStream << "Z" << std::setw ( 2 ) << std::setfill ( '0' ) << n << "H.BMX";
        FileManager::getInstance()->load ( &m_horizon, horizonStream.str() );

        std::stringstream textureStream;
        textureStream << "Z" << std::setw ( 2 ) << std::setfill ( '0' ) << n << "L.SCX";
        ScreenResource textures;
        FileManager::getInstance()->load ( &textures, textureStream.str() );
        if ( m_terrain )
        {
            delete m_terrain;
        }
        const int TERRAIN_IMAGE_WIDTH = 172;
        const int TERRAIN_IMAGE_HEIGHT = 130;
        m_terrain = new Image ( TERRAIN_IMAGE_WIDTH, TERRAIN_IMAGE_HEIGHT, textures.getImage()->getPixels() );
        const int POPUP_IMAGE_WIDTH = 776;
        const int POPUP_IMAGE_HEIGHT = 2;
        const unsigned int POP_IMAGE_OFFSET = SCREEN_WIDTH * ( SCREEN_HEIGHT - 5 );
        m_popUp = new Image ( POPUP_IMAGE_WIDTH, POPUP_IMAGE_HEIGHT, textures.getImage()->getPixels() + POP_IMAGE_OFFSET );

        unsigned int i = 0;
        bool found = true;
        while ( found )
        {
            std::stringstream spriteStream;
            spriteStream << "Z" << std::setw ( 2 ) << std::setfill ( '0' ) << n << "SLOT" << std::setw ( 1 ) << i << ".BMX";
            found = FileManager::getInstance()->resourceExists ( spriteStream.str() );
            if ( found )
            {
                ImageResource spriteSlot;
                FileManager::getInstance()->load ( &spriteSlot, spriteStream.str() );
                for ( unsigned int j = 0; j < spriteSlot.getNumImages(); j++ )
                {
                    Image *img = new Image ( spriteSlot.getImage ( j ) );
                    m_sprites.push_back ( img );
                }
                i++;
            }
        }

        for ( unsigned int y = 1; y <= MAX_TILES; y++ )
        {
            for ( unsigned int x = 1; x <= MAX_TILES; x++ )
            {
                std::stringstream tileStream;
                tileStream << "T" << std::setw ( 2 ) << std::setfill ( '0' ) << n
                           << std::setw ( 2 ) << std::setfill ( '0' ) << x
                           << std::setw ( 2 ) << std::setfill ( '0' ) << y << ".WLD";
                if ( FileManager::getInstance()->resourceExists ( tileStream.str() ) )
                {
                    TileWorldResource *tile = new TileWorldResource;
                    FileManager::getInstance()->load ( tile, tileStream.str() );
                    std::pair<unsigned int, unsigned int> coord ( x, y );
                    m_tiles.insert ( std::pair<const std::pair<unsigned int, unsigned int>, TileWorldResource *> ( coord, tile ) );
                }
            }
        }

        std::stringstream tableStream;
        tableStream << "Z" << std::setw ( 2 ) << std::setfill ( '0' ) << n << ".TBL";
        m_table = new TableResource;
        FileManager::getInstance()->load ( m_table, tableStream.str() );
    }
    catch ( Exception &e )
    {
        e.print ( "Zone::load" );
        throw;
    }
}

Image * Zone::getHorizon ( const unsigned int n )
{
    return m_horizon.getImage ( n );
}

Image * Zone::getTerrain() const
{
    return m_terrain;
}

Image* Zone::getPopUp() const
{
    return m_popUp;
}

Image * Zone::getSprite ( const unsigned int n )
{
    if ( n < m_sprites.size() )
    {
        return m_sprites[n];
    }
    else
    {
        throw IndexOutOfRange ( __FILE__, __LINE__ );
    }
}

TileWorldResource * Zone::getTile ( const unsigned int x, const unsigned int y )
{
    std::pair<unsigned int, unsigned int> coord ( x, y );
    std::map<const std::pair<unsigned int, unsigned int>, TileWorldResource *>::iterator it = m_tiles.find ( coord );
    if ( it != m_tiles.end() )
    {
        return it->second;
    }
    return 0;
}

TableResource * Zone::getTable()
{
    return m_table;
}
