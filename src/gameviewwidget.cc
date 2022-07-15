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

#include "gameviewwidget.h"

GameViewWidget::GameViewWidget(const Rectangle &r, Game *g)
    : ContainerWidget(r)
    , m_game(g)
    , m_cachedImage(0)
{
    m_cachedImage = new Image(m_rect.getWidth(), m_rect.getHeight());
}

GameViewWidget::~GameViewWidget()
{
    if (m_cachedImage)
    {
        delete m_cachedImage;
    }
}

void
GameViewWidget::draw()
{
    if (isVisible())
    {
        if (m_cachedImage)
        {
            m_cachedImage->draw(m_rect.getXPos(), m_rect.getYPos());
        }
        DrawChildWidgets();
    }
}

void
GameViewWidget::update()
{
    redraw();
    if (m_cachedImage)
    {
        m_cachedImage->read(m_rect.getXPos(), m_rect.getYPos());
    }
}
