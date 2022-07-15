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

#ifndef FONT_H
#define FONT_H

#include <vector>
#include <stdint.h>

const unsigned int MAX_FONT_HEIGHT = 16;

typedef uint16_t GlyphData[MAX_FONT_HEIGHT];

struct FontGlyph
{
    unsigned int width;
    GlyphData data;
};

class Font
{
private:
    unsigned int m_first;
    int m_height;
    std::vector<FontGlyph> m_fontGlyphs;
public:
    Font();
    virtual ~Font();
    unsigned int getFirst() const;
    void setFirst ( unsigned int n );
    int getHeight() const;
    void setHeight ( int h );
    int getWidth ( unsigned int n ) const;
    unsigned int getSize() const;
    FontGlyph& getGlyph ( unsigned int n );
    void addGlyph ( FontGlyph& glyph );
    void drawChar ( int x, int y, int ch, int color, bool italic );
};

#endif
