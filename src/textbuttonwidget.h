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

#ifndef TEXT_BUTTON_WIDGET_H
#define TEXT_BUTTON_WIDGET_H

#include "buttonwidget.h"
#include "textwidget.h"

class TextButtonWidget
    : public ButtonWidget
{
private:
    TextWidget* m_label;
public:
    TextButtonWidget ( const Rectangle &r, const int a );
    virtual ~TextButtonWidget();
    void setLabel ( const std::string& s, Font *f );
    void draw();
    void leftClick ( const bool toggle, const int x, const int y );
    void rightClick ( const bool toggle, const int x, const int y );
};

#endif
