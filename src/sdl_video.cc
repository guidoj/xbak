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
#include "sdl_video.h"

SDL_Video::SDL_Video()
    : Video()
    , m_window(0)
    , m_windowSurface (0)
    , m_hiResLoColBuffer(0)
    , m_loResHiColBuffer(0)
    , m_currentVideoBuffer (m_loResHiColBuffer)
    , m_currentPalette(0)
{
}

SDL_Video::~SDL_Video()
{
    if (m_loResHiColBuffer != 0)
    {
        SDL_FreeSurface(m_loResHiColBuffer);
    }
    if (m_hiResLoColBuffer != 0)
    {
        SDL_FreeSurface(m_hiResLoColBuffer);
    }
    if (m_window != 0)
    {
        SDL_DestroyWindow(m_window);
    }
}

void SDL_Video::setMode ( const VideoMode m )
{
    m_mode = m;
    switch (m_mode)
    {
    case HIRES_LOCOL:
        m_currentVideoBuffer = m_hiResLoColBuffer;
        break;
    case LORES_HICOL:
        m_currentVideoBuffer = m_loResHiColBuffer;
        break;
    default:
        break;
    }
}

void SDL_Video::createWindow()
{
    SDL_ShowCursor(SDL_DISABLE);

    m_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (m_window == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    m_windowSurface = SDL_GetWindowSurface(m_window);

    m_hiResLoColBuffer = SDL_CreateRGBSurface(0, HIRES_LOCOL_WIDTH, HIRES_LOCOL_HEIGHT, HIRES_LOCOL_DEPTH, 0, 0, 0, 0);
    if (m_hiResLoColBuffer == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }

    m_loResHiColBuffer = SDL_CreateRGBSurface(0, LORES_HICOL_WIDTH, LORES_HICOL_HEIGHT, LORES_HICOL_DEPTH, 0, 0, 0, 0);
    if (m_loResHiColBuffer == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }

    m_currentPalette = SDL_AllocPalette(PALETTE_COLORS);
    if (m_currentPalette == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    SDL_SetSurfacePalette(m_currentVideoBuffer, m_currentPalette);
}

void SDL_Video::clear()
{
    SDL_FillRect(m_currentVideoBuffer, 0, 0);
}

void SDL_Video::clear(const int x, const int y, const int w, const int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(m_currentVideoBuffer, &rect, 0);
}

unsigned int SDL_Video::getPixel(const int x, const int y)
{
    if ((x >= 0) && (x < m_currentVideoBuffer->w) && (y >= 0) && (y < m_currentVideoBuffer->h))
    {
        uint8_t *p = (uint8_t *) m_currentVideoBuffer->pixels + y * m_currentVideoBuffer->pitch + x;
        return (unsigned int)(*p);
    }
    return 0;
}

void SDL_Video::putPixel(const int x, const int y, const unsigned int c)
{
    if ((x >= 0) && (x < m_currentVideoBuffer->w) && (y >= 0) && (y < m_currentVideoBuffer->h))
    {
        uint8_t *p = (uint8_t *) m_currentVideoBuffer->pixels + y * m_currentVideoBuffer->pitch + x;
        *p = (uint8_t)c;
    }
}

void SDL_Video::drawHLine(const int x, const int y, const int w, const unsigned int c)
{
    int xx = (x < 0 ? 0 : (x < m_currentVideoBuffer->w ? x : m_currentVideoBuffer->w));
    int yy = (y < 0 ? 0 : (y < m_currentVideoBuffer->h ? y : m_currentVideoBuffer->h));
    int ww = w + x - xx;
    if (ww <= 0)
    {
        return;
    }
    if (ww + xx > m_currentVideoBuffer->w)
    {
        ww = m_currentVideoBuffer->w - xx;
    }
    SDL_Rect rect = {xx, yy, ww, 1};
    SDL_FillRect( m_currentVideoBuffer, &rect, c);
}

void SDL_Video::drawVLine(const int x, const int y, const int h, const unsigned int c)
{
    int xx = (x < 0 ? 0 : (x < m_currentVideoBuffer->w ? x : m_currentVideoBuffer->w));
    int yy = (y < 0 ? 0 : (y < m_currentVideoBuffer->h ? y : m_currentVideoBuffer->h));
    int hh = h + y - yy;
    if (hh + yy > m_currentVideoBuffer->h)
    {
        hh = m_currentVideoBuffer->h - yy;
    }
    SDL_Rect rect = {xx, yy, 1, hh};
    SDL_FillRect( m_currentVideoBuffer, &rect, c);
}

#define swap(a,b) { int h = a; a = b; b = h; }

void SDL_Video::drawLine(int x1, int y1, int x2, int y2, const unsigned int c)
{
    // Bresenham's line algorithm
    bool steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep)
    {
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int err = 0;
    int yy;
    if (y1 < y2)
    {
        yy = 1;
    }
    else
    {
        yy = -1;
    }
    int y = y1;
    for (int x = x1; x <= x2; x++)
    {
        if (steep)
        {
            putPixel(y, x, c);
        }
        else
        {
            putPixel(x, y, c);
        }
        err += dy;
        if ((err + err) >= dx)
        {
            y += yy;
            err -= dx;
        }
    }
}

void SDL_Video::drawRect(const int x, const int y, const int w, const int h, const unsigned int c)
{
    SDL_Rect top = {x, y, w, 1};
    SDL_FillRect(m_currentVideoBuffer, &top, c);
    SDL_Rect left = {x, y, 1, h};
    SDL_FillRect(m_currentVideoBuffer, &left, c);
    SDL_Rect right = {x + w - 1, y, 1, h};
    SDL_FillRect(m_currentVideoBuffer, &right, c);
    SDL_Rect bottom = {x, y + h - 1, w, 1};
    SDL_FillRect(m_currentVideoBuffer, &bottom, c);
}

void SDL_Video::fillRect(const int x, const int y, const int w, const int h, const unsigned int c)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect( m_currentVideoBuffer, &rect, c);
}

void SDL_Video::fillRect(const int x, const int y, const int w, const int h,
                         uint8_t *p, const int xx, const int yy, const int ww)
{
    p += (yy + y) * ww + xx + x;
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            putPixel(i, j, *p++);
        }
        p += ww - w;
    }
}

void SDL_Video::drawPolygon(const int *x, const int *y, const unsigned int n, const unsigned int c)
{
    for (unsigned int i = 1; i < n; i++)
    {
        drawLine(x[i-1], y[i-1], x[i], y[i], c);
    }
    drawLine(x[n-1], y[n-1], x[0], y[0], c);
}

bool SDL_Video::createEdge(PolygonEdge &edge, const int x1, const int y1, const int x2, const int y2)
{
    if (y1 == y2)
    {
        return false;
    }
    else
    {
        if (y1 < y2)
        {
            edge.x0 = x1;
            edge.y0 = y1;
            edge.x1 = x2;
            edge.y1 = y2;
        }
        else
        {
            edge.x0 = x2;
            edge.y0 = y2;
            edge.x1 = x1;
            edge.y1 = y1;
        }
        edge.dxdy = (double)(edge.x1 - edge.x0) / (double)(edge.y1 - edge.y0);
        return true;
    }
}

void SDL_Video::sortEdges(PolygonEdge* &edges, const unsigned int n)
{
    unsigned int m = 1;
    while (m < n)
    {
        unsigned int i = 0;
        PolygonEdge pe;
        memcpy(&pe, &edges[m], sizeof(PolygonEdge));
        while ((i < m) && ((edges[i].y0 < pe.y0) || ((edges[i].y0 == pe.y0) && (edges[i].x0 < pe.x0)) ||
                           ((edges[i].y0 == pe.y0) && (edges[i].x0 == pe.x0) && (edges[i].y1 < pe.y1))))
        {
            i++;
        }
        for (unsigned int j = m; j > i; j--)
        {
            memcpy(&edges[j], &edges[j-1], sizeof(PolygonEdge));
        }
        memcpy(&edges[i], &pe, sizeof(PolygonEdge));
        m++;
    }
}

void SDL_Video::fillPolygon(const int* x, const int* y, const unsigned int n, const unsigned int c)
{
    PolygonEdge *edges = new PolygonEdge[n];
    unsigned int m = 0;
    if (createEdge(edges[m], x[n-1], y[n-1], x[0], y[0]))
    {
        m++;
    }
    for (unsigned int i = 1; i < n; i++)
    {
        if (createEdge(edges[m], x[i-1], y[i-1], x[i], y[i]))
        {
            m++;
        }
    }
    sortEdges(edges, m);
    unsigned int l = 0;
    while (l < m)
    {
        bool draw = false;
        int xx = edges[l].x0;
        int yy = edges[l].y0;
        bool isdot = (yy == edges[l].y1);
        unsigned int i = l + 1;
        while ((i < m) && (edges[i].y0 == yy))
        {
            if (!(isdot && (xx == edges[i].x0) && (yy < edges[i].y1)))
            {
                draw = !draw;
            }
            if (draw)
            {
                drawHLine(xx, yy, edges[i].x0 - xx + 1, c);
            }
            xx = edges[i].x0;
            isdot = (yy == edges[i].y1);
            i++;
        }
        i = l;
        while ((i < m) && (edges[i].y0 == yy))
        {
            if (edges[i].y1 > yy)
            {
                edges[i].y0++;
            }
            edges[i].x0 = edges[i].x1 - (int)(((double)(edges[i].y1 - edges[i].y0) * edges[i].dxdy) - 0.5);
            i++;
        }
        sortEdges(edges, m);
        while ((l < m) && (edges[l].y1 == yy))
        {
            l++;
        }
    }
    delete[] edges;
}

void SDL_Video::fillPolygon(const int* x, const int* y, const unsigned int n,
                            uint8_t *p, const int xx, const int yy, const int ww)
{
    PolygonEdge *edges = new PolygonEdge[n];
    unsigned int m = 0;
    if (createEdge(edges[m], x[n-1], y[n-1], x[0], y[0]))
    {
        m++;
    }
    for (unsigned int i = 1; i < n; i++)
    {
        if (createEdge(edges[m], x[i-1], y[i-1], x[i], y[i]))
        {
            m++;
        }
    }
    sortEdges(edges, m);
    unsigned int l = 0;
    while (l < m)
    {
        bool draw = false;
        int x0 = edges[l].x0;
        int y0 = edges[l].y0;
        bool isdot = (y0 == edges[l].y1);
        unsigned int i = l + 1;
        while ((i < m) && (edges[i].y0 == y0))
        {
            if (!(isdot && (x0 == edges[i].x0) && (y0 < edges[i].y1)))
            {
                draw = !draw;
            }
            if (draw)
            {
                if ((y0 >= 0) && (y0 < m_currentVideoBuffer->h))
                {
                    uint8_t *q = p + (yy + y0) * ww + xx + x0;
                    for (int x1 = x0 < 0 ? 0 : (x0 < m_currentVideoBuffer->w ? x0 : m_currentVideoBuffer->w - 1); (x1 <= edges[i].x0) && (x1 < m_currentVideoBuffer->w); x1++)
                    {
                        putPixel(x1, y0, *q++);
                    }
                }
            }
            x0 = edges[i].x0;
            isdot = (y0 == edges[i].y1);
            i++;
        }
        i = l;
        while ((i < m) && (edges[i].y0 == y0))
        {
            if (edges[i].y1 > y0)
            {
                edges[i].y0++;
            }
            edges[i].x0 = edges[i].x1 - (int)(((double)(edges[i].y1 - edges[i].y0) * edges[i].dxdy) - 0.5);
            i++;
        }
        sortEdges(edges, m);
        while ((l < m) && (edges[l].y1 == y0))
        {
            l++;
        }
    }
    delete[] edges;
}

void
SDL_Video::readImage(const int x, const int y, const int w, const int h, uint8_t *p)
{
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            *p++ = getPixel(i, j);
        }
    }
}

void
SDL_Video::drawImage(const int x, const int y, const int w, const int h, uint8_t *p)
{
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            putPixel(i, j, *p++);
        }
    }
}

void
SDL_Video::drawImage(const int x, const int y, const int w, const int h, uint8_t *p, const uint8_t transparant)
{
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            if (*p != transparant)
            {
                putPixel(i, j, *p);
            }
            p++;
        }
    }
}

void
SDL_Video::drawImage(const int x, const int y, const int w, const int,
                     const int xx, const int yy, const int ww, const int hh, uint8_t *p)
{
    p += yy * w;
    for (int j = y + yy; j < y + yy + hh; j++)
    {
        p += xx;
        for (int i = x + xx; i < x + xx + ww; i++)
        {
            putPixel(i, j, *p);
            p++;
        }
        p += w - ww - xx;
    }
}

void
SDL_Video::drawImage(const int x, const int y, const int w, const int,
                     const int xx, const int yy, const int ww, const int hh,
                     uint8_t *p, const uint8_t transparant)
{
    p += yy * w;
    for (int j = y + yy; j < y + yy + hh; j++)
    {
        p += xx;
        for (int i = x + xx; i < x + xx + ww; i++)
        {
            if (*p != transparant)
            {
                putPixel(i, j, *p);
            }
            p++;
        }
        p += w - ww - xx;
    }
}

void
SDL_Video::drawGlyph(const int x, const int y, const int w, const int h, const uint8_t c, uint16_t *p)
{
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            if (*p & (0x8000 >> i))
            {
                putPixel(x + i, y + j, c);
            }
        }
        p++;
    }
}

void
SDL_Video::drawGlyphItalic(const int x, const int y, const int w, const int h, const uint8_t c, uint16_t *p)
{
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            if (*p & (0x8000 >> i))
            {
                putPixel(x + i + 4 - (j / 3), y + j, c);
            }
        }
        p++;
    }
}

void
SDL_Video::getPalette(Color *color, const unsigned int first, const unsigned int n)
{
    if (m_currentVideoBuffer->format->palette)
    {
        memcpy(color, &( m_currentVideoBuffer->format->palette->colors[first]), n * sizeof(SDL_Color));
    }
}

void
SDL_Video::setPalette(Color *color, const unsigned int first, const unsigned int n)
{
    SDL_SetPaletteColors(m_currentPalette, (SDL_Color *)color, first, n);
    SDL_SetSurfacePalette(m_currentVideoBuffer, m_currentPalette);
}

void
SDL_Video::refresh()
{
    SDL_Surface *tmp = SDL_ConvertSurfaceFormat(m_currentVideoBuffer, m_windowSurface->format->format, 0);
    SDL_BlitScaled(tmp, 0, m_windowSurface, 0);
    SDL_UpdateWindowSurface(m_window);
    SDL_FreeSurface(tmp);
}

void
SDL_Video::grabInput(const bool toggle)
{
    SDL_SetWindowGrab(m_window, toggle ? SDL_TRUE : SDL_FALSE);
}

void
SDL_Video::saveScreenShot(const std::string& filename)
{
    SDL_SaveBMP(m_windowSurface, filename.c_str());
}
