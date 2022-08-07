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

#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include <string>

const int WINDOW_WIDTH  = 640;
const int WINDOW_HEIGHT = 400;
const int WINDOW_DEPTH  = 32;

const int HIRES_LOCOL_WIDTH  = 640;
const int HIRES_LOCOL_HEIGHT = 350;
const int HIRES_LOCOL_DEPTH  = 8;

const int LORES_HICOL_WIDTH  = 320;
const int LORES_HICOL_HEIGHT = 200;
const int LORES_HICOL_DEPTH  = 8;

const int PALETTE_COLORS = 256;

const char WINDOW_TITLE[] = "xbak";

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

typedef enum
{
    HIRES_LOCOL,
    LORES_HICOL
}
VideoMode;

class Video
{
protected:
    VideoMode m_mode;

public:
    Video();
    virtual ~Video();
    virtual void setMode ( const VideoMode m ) = 0;
    virtual void createWindow() = 0;
    virtual void clear() = 0;
    virtual void clear ( const int x, const int y, const int w, const int h ) = 0;
    virtual void drawHLine ( const int x, const int y, const int w, const unsigned int c ) = 0;
    virtual void drawVLine ( const int x, const int y, const int h, const unsigned int c ) = 0;
    virtual void drawLine ( int x1, int y1, int x2, int y2, const unsigned int c ) = 0;
    virtual void drawRect ( const int x, const int y, const int w, const int h, const unsigned int c ) = 0;
    virtual void fillRect ( const int x, const int y, const int w, const int h, const unsigned int c ) = 0;
    virtual void fillRect ( const int x, const int y, const int w, const int h,
                            uint8_t *p, const int xx, const int yy, const int ww ) = 0;
    virtual void drawPolygon ( const int *x, const int *y, const unsigned int n, const unsigned int c ) = 0;
    virtual void fillPolygon ( const int *x, const int *y, const unsigned int n, const unsigned int c ) = 0;
    virtual void fillPolygon ( const int* x, const int* y, const unsigned int n,
                               uint8_t *p, const int xx, const int yy, const int ww) = 0;
    virtual void readImage ( const int x, const int y, const int w, const int h, uint8_t *p ) = 0;
    virtual void drawImage ( const int x, const int y, const int w, const int h, uint8_t *p ) = 0;
    virtual void drawImage ( const int x, const int y, const int w, const int h, uint8_t *p, const uint8_t transparant ) = 0;
    virtual void drawImage ( const int x, const int y, const int w, const int h,
                             const int xx, const int yy, const int ww, const int hh, uint8_t *p ) = 0;
    virtual void drawImage ( const int x, const int y, const int w, const int h,
                             const int xx, const int yy, const int ww, const int hh,
                             uint8_t *p, const uint8_t transparant ) = 0;
    virtual void drawGlyph ( const int x, const int y, const int w, const int h, const uint8_t c, uint16_t *p ) = 0;
    virtual void drawGlyphItalic ( const int x, const int y, const int w, const int h, const uint8_t c, uint16_t *p ) = 0;
    virtual void getPalette ( Color *color, const unsigned int first, const unsigned int n ) = 0;
    virtual void setPalette ( Color *color, const unsigned int first, const unsigned int n ) = 0;
    virtual void refresh() = 0;
    virtual void grabInput ( const bool toggle ) = 0;
    virtual void saveScreenShot ( const std::string& filename ) = 0;
};

#endif

