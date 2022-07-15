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

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

#include "filebuffer.h"

class Image
{
private:
    int m_width;
    int m_height;
    unsigned int m_flags;
    bool m_highres_lowcol;
    uint8_t *m_pixel;
public:
    Image ( const int w, const int h );
    Image ( const int w, const int h, const unsigned int f );
    Image ( const int w, const int h, const bool hrlc );
    Image ( const int w, const int h, const uint8_t *p );
    Image ( Image *img );
    Image ( const int w, const int h, Image *img );
    Image ( const int w, const int h, std::vector<Image *> &img );
    ~Image();
    int getWidth() const;
    int getHeight() const;
    unsigned int getSize() const;
    unsigned int getFlags() const;
    void setFlags ( const unsigned int f );
    bool isHighResLowCol() const;
    uint8_t getPixel ( const int x, const int y ) const;
    uint8_t * getPixels() const;
    void setPixel ( const int x, const int y, const uint8_t color );
    void setPixels ( uint8_t *data, unsigned int size = 0 );
    void horizontalFlip();
    void verticalFlip();
    void fill ( const uint8_t color );
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
    void read ( const int x, const int y );
    void draw ( const int x, const int y ) const;
    void draw ( const int x, const int y, const uint8_t transparent ) const;
    void draw ( const int x, const int y, const int xoff, const int yoff, const int w, const int h ) const;
    void draw ( const int x, const int y, const int xoff, const int yoff, const int w, const int h, const uint8_t transparent ) const;
};

#endif
