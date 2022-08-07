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

#include <cstring>

#include "exception.h"
#include "palette.h"

Palette::Palette(const unsigned int n)
    : m_size(n)
{
    m_colors = new Color[m_size];
    m_media = MediaToolkit::getInstance();
}

Palette::~Palette()
{
    if (m_colors)
    {
        delete[] m_colors;
    }
}

unsigned int
Palette::getSize() const
{
    return m_size;
}

Color&
Palette::getColor(const unsigned int i) const
{
    return m_colors[i];
}

void
Palette::setColor(const unsigned int i, const Color &c)
{
    memcpy(&(m_colors[i]), &c, sizeof(Color));
}

void
Palette::fill()
{
    if (m_colors)
    {
        delete[] m_colors;
    }
    m_size = PALETTE_COLORS;
    m_colors = new Color[m_size];
    memset(m_colors, 0, m_size * sizeof(Color));
    m_colors[0].r = 0;
    m_colors[0].g = 0;
    m_colors[0].b = 0;
    m_colors[0].a = 0;
    m_colors[15].r = 255;
    m_colors[15].g = 255;
    m_colors[15].b = 255;
    m_colors[15].a = 0;
}

void
Palette::activate(const unsigned int first, const unsigned int n)
{
    m_media->getVideo()->setPalette(m_colors, first, n);
}

void
Palette::retrieve(const unsigned int first, const unsigned int n)
{
    if ((m_colors != 0) && (m_size < (first + n)))
    {
        delete[] m_colors;
        m_colors = 0;
    }
    if (!m_colors)
    {
        m_size = first + n;
        m_colors = new Color[m_size];
    }
    m_media->getVideo()->getPalette(m_colors, first, n);
}

void
Palette::fadeFrom(Color* from, const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay)
{
    Color* tmp = new Color[PALETTE_COLORS];
    for (unsigned int i = 0; i <= steps; i++)
    {
        double x = (double)i / (double)steps;
        for (unsigned int j = first; j < first + n; j++)
        {
            tmp[j].r = from[j].r + (int)((m_colors[j].r - from[j].r) * x);
            tmp[j].g = from[j].g + (int)((m_colors[j].g - from[j].g) * x);
            tmp[j].b = from[j].b + (int)((m_colors[j].b - from[j].b) * x);
        }
        m_media->getVideo()->setPalette(&tmp[first], first, n);
        m_media->getVideo()->refresh();
        m_media->getClock()->delay(delay);
        m_media->pollEvents();
    }
    delete[] tmp;
}

void
Palette::fadeTo(Color* to, const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay)
{
    Color* tmp = new Color[PALETTE_COLORS];
    m_media->getVideo()->getPalette(tmp, 0, PALETTE_COLORS);
    for (unsigned int i = 0; i <= steps; i++)
    {
        double x = (double)i / (double)steps;
        for (unsigned int j = first; j < first + n; j++)
        {
            tmp[j].r = m_colors[j].r + (int)((to[j].r - m_colors[j].r) * x);
            tmp[j].g = m_colors[j].g + (int)((to[j].g - m_colors[j].g) * x);
            tmp[j].b = m_colors[j].b + (int)((to[j].b - m_colors[j].b) * x);
        }
        m_media->getVideo()->setPalette(&tmp[first], first, n);
        m_media->getVideo()->refresh();
        m_media->getClock()->delay(delay);
        m_media->pollEvents();
    }
    delete[] tmp;
}

void
Palette::fadeIn(const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay)
{
    Color* from = new Color[PALETTE_COLORS];
    memset(from, 0, PALETTE_COLORS * sizeof(Color));
    fadeFrom(from, first, n, steps, delay);
    delete[] from;
}

void
Palette::fadeOut(const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay)
{
    Color* to = new Color[PALETTE_COLORS];
    memset(to, 0, PALETTE_COLORS * sizeof(Color));
    fadeTo(to, first, n, steps, delay);
    delete[] to;
}
