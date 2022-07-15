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

#ifndef PALETTE_H
#define PALETTE_H

#include "mediatoolkit.h"

class Palette
{
private:
    unsigned int m_size;
    Color *m_colors;
    bool m_delayed;
    MediaToolkit *m_media;
public:
    Palette ( const unsigned int n );
    ~Palette();
    unsigned int getSize() const;
    Color& getColor ( const unsigned int i ) const;
    void setColor ( const unsigned int i, const Color &c );
    void fill();
    void activate ( const unsigned int first, const unsigned int n );
    void retrieve ( const unsigned int first, const unsigned int n );
    void fadeFrom ( Color* from, const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay );
    void fadeTo ( Color* from, const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay );
    void fadeIn ( const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay );
    void fadeOut ( const unsigned int first, const unsigned int n, const unsigned int steps, const unsigned int delay );
    void timerExpired ( const TimerEvent &te );
};

#endif

