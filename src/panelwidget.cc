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

#include "exception.h"
#include "mediatoolkit.h"
#include "panelwidget.h"

PanelWidget::PanelWidget(const Rectangle &r)
    : ContainerWidget(r)
    , m_background(0)
{}

PanelWidget::~PanelWidget()
{}

void
PanelWidget::setBackground(Image *img)
{
    if (!img)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_background = img;
}

void
PanelWidget::draw()
{
    if (isVisible())
    {
        MediaToolkit::getInstance()->getVideo()->clear(m_rect.getXPos(), m_rect.getYPos(), m_rect.getWidth(), m_rect.getHeight());
        if (m_background)
        {
            m_background->draw(m_rect.getXPos(), m_rect.getYPos());
        }
        DrawChildWidgets();
    }
}
