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

#ifndef CHOICE_WIDGET_H
#define CHOICE_WIDGET_H

#include "image.h"
#include "widget.h"

class ChoiceWidget
    : public ActiveWidget
{
private:
    Image *m_normalImage;
    Image *m_selectedImage;
public:
    ChoiceWidget ( const Rectangle &r, const int a );
    virtual ~ChoiceWidget();
    void setImage ( Image *normal, Image *selected );
    void draw();
    void leftClick ( const bool toggle, const int x, const int y );
    void rightClick ( const bool toggle, const int x, const int y );
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif

