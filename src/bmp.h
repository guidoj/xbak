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

#ifndef BMP_H
#define BMP_H

#include "image.h"
#include "palette.h"

class BMP
{
private:
    Image *m_image;
    Palette *m_palette;
public:
    BMP();
    virtual ~BMP();
    Image * getImage() const;
    void setImage ( Image *img );
    Palette * getPalette() const;
    void setPalette ( Palette *pal );
    void load ( const std::string &name );
    void save ( const std::string &name );
};

#endif
