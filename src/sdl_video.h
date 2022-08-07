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

#ifndef SDL_VIDEO_H
#define SDL_VIDEO_H

#include <SDL.h>

#include "video.h"

struct PolygonEdge
{
    int x0;
    int y0;
    int x1;
    int y1;
    double dxdy;
};

class SDL_Video
    : public Video
{
private:
    SDL_Window* m_window;
    SDL_Surface* m_windowSurface;
    SDL_Surface* m_hiResLoColBuffer;
    SDL_Surface* m_loResHiColBuffer;
    SDL_Surface* m_currentVideoBuffer;
    SDL_Palette *m_currentPalette;

    bool createEdge ( PolygonEdge &edge, const int x1, const int y1, const int x2, const int y2 );
    void sortEdges ( PolygonEdge* &edges, const unsigned int n );
    unsigned int getPixel ( const int x, const int y );
    void putPixel ( const int x, const int y, const unsigned int c );

public:
    SDL_Video();
    ~SDL_Video();
    void setMode ( const VideoMode m );
    void createWindow();
    void drawHLine ( const int x, const int y, const int w, const unsigned int c );
    void drawVLine ( const int x, const int y, const int h, const unsigned int c );
    void drawLine ( int x1, int y1, int x2, int y2, const unsigned int c );
    void drawRect ( const int x, const int y, const int w, const int h, const unsigned int c );
    void fillRect ( const int x, const int y, const int w, const int h, const unsigned int c );
    void fillRect ( const int x, const int y, const int w, const int h,
                    uint8_t *p, const int xx, const int yy, const int ww );
    void drawPolygon ( const int *x, const int *y, const unsigned int n, const unsigned int c );
    void fillPolygon ( const int *x, const int *y, const unsigned int n, const unsigned int c );
    void fillPolygon ( const int* x, const int* y, const unsigned int n,
                       uint8_t *p, const int xx, const int yy, const int ww);
    void readImage ( const int x, const int y, const int w, const int h, uint8_t *p );
    void drawImage ( const int x, const int y, const int w, const int h, uint8_t *p );
    void drawImage ( const int x, const int y, const int w, const int h, uint8_t *p, const uint8_t transparant );
    void drawImage ( const int x, const int y, const int w, const int h,
                     const int xx, const int yy, const int ww, const int hh, uint8_t *p );
    void drawImage ( const int x, const int y, const int w, const int h,
                     const int xx, const int yy, const int ww, const int hh,
                     uint8_t *p, const uint8_t transparant );
    void drawGlyph ( const int x, const int y, const int w, const int h, const uint8_t c, uint16_t*p );
    void drawGlyphItalic ( const int x, const int y, const int w, const int h, const uint8_t c, uint16_t*p );
    void getPalette ( Color *color, const unsigned int first, const unsigned int n );
    void setPalette ( Color *color, const unsigned int first, const unsigned int n );
    void clear();
    void clear ( const int x, const int y, const int w, const int h );
    void refresh();
    void grabInput ( const bool toggle );
    void saveScreenShot ( const std::string& filename );
};

#endif
