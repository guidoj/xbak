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

#include "textwidget.h"

TextWidget::TextWidget ( const Rectangle &r, Font *f )
    : Widget ( r )
    , m_font ( f )
    , m_textBlock()
    , m_textWidth ( 0 )
    , m_textHeight ( 0 )
    , m_horAlign ( HA_CENTER )
    , m_vertAlign ( VA_CENTER )
{
}

TextWidget::~TextWidget()
{
}

void TextWidget::setText ( const std::string &s )
{
    m_textBlock.setWords ( s );
    m_textWidth = 0;
    for ( unsigned int i = 0; i < s.size(); i++ )
    {
        m_textWidth += m_font->getWidth ( s[i] - m_font->getFirst() );
    }
    m_textHeight = m_font->getHeight();
}

void TextWidget::setColor ( const int c )
{
    m_textBlock.setColor ( c );
}

void TextWidget::setShadow ( const int s, const int xoff, const int yoff )
{
    m_textBlock.setShadow ( s );
    m_textBlock.setShadowXOff ( xoff );
    m_textBlock.setShadowYOff ( yoff );
}

void TextWidget::setAlignment ( const HorizontalAlignment ha, const VerticalAlignment va )
{
    m_horAlign = ha;
    m_vertAlign = va;
}

void TextWidget::setItalic ( const bool it )
{
    m_textBlock.setItalic ( it );
}

void TextWidget::draw()
{
    if ( isVisible() )
    {
        int xoff = 0;
        int yoff = 0;
        switch ( m_horAlign )
        {
        case HA_LEFT:
            xoff = 0;
            break;
        case HA_CENTER:
            xoff = ( m_rect.getWidth() - m_textWidth ) / 2;
            break;
        case HA_RIGHT:
            xoff = m_rect.getWidth() - m_textWidth;
            break;
        case HA_FILL:
            xoff = 0;
            break;
        }
        switch ( m_vertAlign )
        {
        case VA_TOP:
            yoff = 0;
            break;
        case VA_CENTER:
            yoff = ( m_rect.getHeight() - m_textHeight ) / 2;
            break;
        case VA_BOTTOM:
            yoff = m_rect.getHeight() - m_textHeight;
            break;
        }
        m_textBlock.draw(m_rect.getXPos() + xoff, m_rect.getYPos() + yoff, m_rect.getWidth(), m_rect.getHeight(), m_font);
    }
}

void TextWidget::drag ( const int, const int )
{
}

void TextWidget::drop ( const int, const int )
{
}
