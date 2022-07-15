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
    , m_info(SDL_GetVideoInfo())
    , m_window(0)
    , m_windowBuffer(0)
    , m_hireslocolSurface()
    , m_loreshicolSurface()
    , m_currentSurface(&m_loreshicolSurface)
{
    m_hireslocolSurface.buffer = 0;
    m_loreshicolSurface.buffer = 0;
}

SDL_Video::~SDL_Video()
{
    if (m_loreshicolSurface.buffer != 0)
    {
        SDL_FreeSurface(m_loreshicolSurface.buffer);
    }
    if (m_hireslocolSurface.buffer != 0)
    {
        SDL_FreeSurface(m_hireslocolSurface.buffer);
    }
    if (m_windowBuffer != 0)
    {
        SDL_FreeSurface(m_windowBuffer);
    }
    if (m_window != 0)
    {
        SDL_FreeSurface(m_window);
    }
}

void SDL_Video::setMode ( const VideoMode m )
{
    m_mode = m;
    switch (m_mode)
    {
    case HIRES_LOWCOL:
        m_currentSurface = &m_hireslocolSurface;
        break;
    case LORES_HICOL:
        m_currentSurface = &m_loreshicolSurface;
        break;
    default:
        break;
    }
}

void SDL_Video::createWindow ( const unsigned int sc )
{
    m_scaling = sc;
    m_width = WINDOW_WIDTH * m_scaling;
    m_height = WINDOW_HEIGHT * m_scaling;

    unsigned int flags = SDL_ANYFORMAT;
    if (m_info->hw_available)
    {
        flags |= SDL_HWSURFACE | SDL_DOUBLEBUF;
    }
    else
    {
        flags |= SDL_SWSURFACE;
    }

    int bpp = SDL_VideoModeOK(m_width, m_height, WINDOW_BPP, flags);
    if (bpp <= 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }

    m_window = SDL_SetVideoMode(m_width, m_height, 0, flags);
    if (m_window == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
    SDL_ShowCursor(SDL_DISABLE);
    SDL_WM_SetCaption(WINDOW_TITLE, 0);

    m_windowBuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, m_width, m_height, WINDOW_BPP, 0, 0, 0, 0);
    if (m_windowBuffer == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }

    m_hireslocolSurface.xOffset = 0;
    m_hireslocolSurface.yOffset = (WINDOW_HEIGHT - HIRES_LOCOL_HEIGHT) / 2;
    m_hireslocolSurface.scaling = m_scaling;
    m_hireslocolSurface.buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, HIRES_LOCOL_WIDTH, HIRES_LOCOL_HEIGHT, WINDOW_BPP, 0, 0, 0, 0);
    if (m_hireslocolSurface.buffer == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }

    m_loreshicolSurface.xOffset = 0;
    m_loreshicolSurface.yOffset = 0;
    m_loreshicolSurface.scaling = 2 * m_scaling;
    m_loreshicolSurface.buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, LORES_HICOL_WIDTH, LORES_HICOL_HEIGHT, WINDOW_BPP, 0, 0, 0, 0);
    if (m_loreshicolSurface.buffer == 0)
    {
        throw SDL_Exception(__FILE__, __LINE__, SDL_GetError());
    }
}

void SDL_Video::clear()
{
    SDL_FillRect(m_currentSurface->buffer, 0, 0);
}

void SDL_Video::clear(const int x, const int y, const int w, const int h)
{
    SDL_Rect rect = {(Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h};
    SDL_FillRect(m_currentSurface->buffer, &rect, 0);
}

unsigned int SDL_Video::getPixel(const int x, const int y)
{
    if ((x >= 0) && (x < m_currentSurface->buffer->w) && (y >= 0) && (y < m_currentSurface->buffer->h))
    {
        uint8_t *p = (uint8_t *)m_currentSurface->buffer->pixels + y * m_currentSurface->buffer->pitch + x;
        return (unsigned int)(*p);
    }
    return 0;
}

void SDL_Video::putPixel(const int x, const int y, const unsigned int c)
{
    if ((x >= 0) && (x < m_currentSurface->buffer->w) && (y >= 0) && (y < m_currentSurface->buffer->h))
    {
        uint8_t *p = (uint8_t *)m_currentSurface->buffer->pixels + y * m_currentSurface->buffer->pitch + x;
        *p = (uint8_t)c;
    }
}

void SDL_Video::drawHLine(const int x, const int y, const int w, const unsigned int c)
{
    int xx = (x < 0 ? 0 : (x < m_currentSurface->buffer->w ? x : m_currentSurface->buffer->w));
    int yy = (y < 0 ? 0 : (y < m_currentSurface->buffer->h ? y : m_currentSurface->buffer->h));
    int ww = w + x - xx;
    if (ww <= 0)
    {
        return;
    }
    if (ww + xx > m_currentSurface->buffer->w)
    {
        ww = m_currentSurface->buffer->w - xx;
    }
    SDL_Rect rect = {(Sint16)xx, (Sint16)yy, (Uint16)ww, 1};
    SDL_FillRect(m_currentSurface->buffer, &rect, c);
}

void SDL_Video::drawVLine(const int x, const int y, const int h, const unsigned int c)
{
    int xx = (x < 0 ? 0 : (x < m_currentSurface->buffer->w ? x : m_currentSurface->buffer->w));
    int yy = (y < 0 ? 0 : (y < m_currentSurface->buffer->h ? y : m_currentSurface->buffer->h));
    int hh = h + y - yy;
    if (hh + yy > m_currentSurface->buffer->h)
    {
        hh = m_currentSurface->buffer->h - yy;
    }
    SDL_Rect rect = {(Sint16)xx, (Sint16)yy, 1, (Uint16)hh};
    SDL_FillRect(m_currentSurface->buffer, &rect, c);
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
    SDL_Rect top = {(Sint16)x, (Sint16)y, (Uint16)w, 1};
    SDL_FillRect(m_currentSurface->buffer, &top, c);
    SDL_Rect left = {(Sint16)x, (Sint16)y, 1, (Uint16)h};
    SDL_FillRect(m_currentSurface->buffer, &left, c);
    SDL_Rect right = {(Sint16)(x + w - 1), (Sint16)y, 1, (Uint16)h};
    SDL_FillRect(m_currentSurface->buffer, &right, c);
    SDL_Rect bottom = {(Sint16)x, (Sint16)(y + h - 1), (Uint16)w, 1};
    SDL_FillRect(m_currentSurface->buffer, &bottom, c);
}

void SDL_Video::fillRect(const int x, const int y, const int w, const int h, const unsigned int c)
{
    SDL_Rect rect = {(Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h};
    SDL_FillRect(m_currentSurface->buffer, &rect, c);
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
                if ((y0 >= 0) && (y0 < m_currentSurface->buffer->h))
                {
                    uint8_t *q = p + (yy + y0) * ww + xx + x0;
                    for (int x1 = x0 < 0 ? 0 : (x0 < m_currentSurface->buffer->w ? x0 : m_currentSurface->buffer->w - 1); (x1 <= edges[i].x0) && (x1 < m_currentSurface->buffer->w); x1++)
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

void SDL_Video::drawImage(const int x, const int y, const int w, const int h, uint8_t *p)
{
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            putPixel(i, j, *p++);
        }
    }
}

void SDL_Video::drawImage(const int x, const int y, const int w, const int h, uint8_t *p, const uint8_t transparant)
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

void SDL_Video::drawImage(const int x, const int y, const int w, const int,
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

void SDL_Video::drawImage(const int x, const int y, const int w, const int,
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

void SDL_Video::drawGlyph(const int x, const int y, const int w, const int h, const uint8_t c, uint16_t *p)
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

void SDL_Video::drawGlyphItalic(const int x, const int y, const int w, const int h, const uint8_t c, uint16_t *p)
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

void SDL_Video::getPalette(Color *color, const unsigned int first, const unsigned int n)
{
    if (m_currentSurface->buffer->format->palette)
    {
        memcpy(color, &(m_currentSurface->buffer->format->palette->colors[first]), n * sizeof(SDL_Color));
    }
}

void SDL_Video::setPalette(Color *color, const unsigned int first, const unsigned int n)
{
    if (m_currentSurface->buffer->format->palette)
    {
        SDL_SetPalette(m_currentSurface->buffer, SDL_LOGPAL, (SDL_Color *)color, first, n);
    }
    if (m_windowBuffer->format->palette)
    {
        SDL_SetPalette(m_windowBuffer, SDL_LOGPAL, (SDL_Color *)color, first, n);
    }
}

void SDL_Video::refresh()
{
    SDL_UpdateRect(m_currentSurface->buffer, 0, 0, 0, 0);
    for (int y = 0; y < m_currentSurface->buffer->h; y++)
    {
        for (int x = 0; x < m_currentSurface->buffer->w; x++)
        {
            memset((uint8_t *)m_windowBuffer->pixels + ((y + m_currentSurface->yOffset) * m_windowBuffer->pitch + (x + m_currentSurface->xOffset)) * m_currentSurface->scaling,
                   *((uint8_t *)m_currentSurface->buffer->pixels + y * m_currentSurface->buffer->pitch + x), m_currentSurface->scaling);
        }
        for (unsigned int i = 1; i < m_currentSurface->scaling; i++)
        {
            memcpy((uint8_t *)m_windowBuffer->pixels + ((y + m_currentSurface->yOffset) * m_currentSurface->scaling + i) * m_windowBuffer->pitch,
                   (uint8_t *)m_windowBuffer->pixels + (y + m_currentSurface->yOffset) * m_currentSurface->scaling * m_windowBuffer->pitch, m_windowBuffer->w);
        }
    }
    SDL_UpdateRect(m_windowBuffer, 0, 0, 0, 0);
    SDL_Surface *tmp = SDL_DisplayFormat(m_windowBuffer);
    SDL_BlitSurface(tmp, 0, m_window, 0);
    SDL_FreeSurface(tmp);
    SDL_Flip(m_window);
}

#ifdef DEBUG
void SDL_Video::GrabInput(const bool)
{
}
#else
void SDL_Video::grabInput(const bool toggle)
{
    SDL_WM_GrabInput(toggle ? SDL_GRAB_ON : SDL_GRAB_OFF);
}
#endif

void SDL_Video::saveScreenShot(const std::string& filename)
{
    SDL_UpdateRect(m_windowBuffer, 0, 0, 0, 0);
    SDL_SaveBMP(m_windowBuffer, filename.c_str());
}
