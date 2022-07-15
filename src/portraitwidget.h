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

#ifndef PORTRAIT_WIDGET_H
#define PORTRAIT_WIDGET_H

#include "playercharacter.h"
#include "widget.h"

class PortraitWidget
    : public Widget
{
private:
    PlayerCharacter *m_playerCharacter;
    Image *m_horizontalBorder;
    Image *m_verticalBorder;
public:
    PortraitWidget ( const Rectangle &r, PlayerCharacter *pc );
    virtual ~PortraitWidget();
    void setBorders ( Image *hb, Image *vb );
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
