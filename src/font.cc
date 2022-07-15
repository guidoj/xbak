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
#include "font.h"
#include "mediatoolkit.h"

Font::Font()
    : m_first ( 0 )
    , m_height ( 0 )
    , m_fontGlyphs ()
{}

Font::~Font()
{
    m_fontGlyphs.clear();
}

unsigned int Font::getFirst() const
{
    return m_first;
}

void Font::setFirst ( unsigned int n )
{
    m_first = n;
}

int Font::getHeight() const
{
    return m_height;
}

void Font::setHeight ( int h )
{
    m_height = h;
}

int Font::getWidth ( unsigned int n ) const
{
    if ( n < m_fontGlyphs.size() )
    {
        return m_fontGlyphs[n].width;
    }
    else
    {
        throw IndexOutOfRange ( __FILE__, __LINE__ );
    }
}

unsigned int Font::getSize() const
{
    return m_fontGlyphs.size();
}

FontGlyph& Font::getGlyph ( unsigned int n )
{
    if ( n < m_fontGlyphs.size() )
    {
        return m_fontGlyphs[n];
    }
    else
    {
        throw IndexOutOfRange ( __FILE__, __LINE__ );
    }
}

void Font::addGlyph ( FontGlyph& glyph )
{
    m_fontGlyphs.push_back ( glyph );
}

void Font::drawChar ( int x, int y, int ch, int color, bool italic )
{
    Video *video = MediaToolkit::getInstance()->getVideo();
    if ( ( int ) ( ch - m_first ) >= 0 )
    {
        if ( italic )
        {
            video->drawGlyphItalic ( x, y, m_fontGlyphs[ch - m_first].width, m_height, color, m_fontGlyphs[ch - m_first].data );
        }
        else
        {
            video->drawGlyph ( x, y, m_fontGlyphs[ch - m_first].width, m_height, color, m_fontGlyphs[ch - m_first].data );
        }
    }
}
