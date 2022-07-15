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

#include "mediatoolkit.h"
#include "worldviewwidget.h"

WorldViewWidget::WorldViewWidget(const Rectangle &r, Game *g)
    : GameViewWidget(r, g)
{
    m_game->getCamera()->attach(this);
    update();
}

WorldViewWidget::~WorldViewWidget()
{
    m_game->getCamera()->detach(this);
}

void
WorldViewWidget::redraw()
{
    MediaToolkit::getInstance()->getVideo()->clear(m_rect.getXPos(), m_rect.getYPos(), m_rect.getWidth(), m_rect.getHeight());
    m_game->getScene()->drawFirstPerson(m_rect.getXPos(), m_rect.getYPos(), m_rect.getWidth(), m_rect.getHeight(), m_game->getCamera());
}
