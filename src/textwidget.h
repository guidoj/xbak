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

#ifndef TEXT_WIDGET_H
#define TEXT_WIDGET_H

#include "font.h"
#include "text.h"
#include "widget.h"

class TextWidget : public Widget
{
private:
    Font *m_font;
    TextBlock m_textBlock;
    int m_textWidth;
    int m_textHeight;
    HorizontalAlignment m_horAlign;
    VerticalAlignment m_vertAlign;
public:
    TextWidget ( const Rectangle &r, Font *f );
    virtual ~TextWidget();
    void setColor ( const int c );
    void setText ( const std::string& s );
    void setShadow ( const int s, const int xoff, const int yoff );
    void setAlignment ( const HorizontalAlignment ha, const VerticalAlignment va );
    void setItalic ( const bool it );
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
