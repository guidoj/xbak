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
#include "portraitwidget.h"

PortraitWidget::PortraitWidget(const Rectangle &r, PlayerCharacter *pc)
    : Widget(r)
    , m_playerCharacter(pc)
    , m_horizontalBorder(0)
    , m_verticalBorder(0)
{}

PortraitWidget::~PortraitWidget()
{}

void
PortraitWidget::setBorders(Image *hb, Image *vb)
{
    if ((!hb) || (!vb))
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_horizontalBorder = hb;
    m_verticalBorder = vb;
}

void
PortraitWidget::draw()
{
    if (isVisible())
    {
        int xoff = 0;
        int yoff = 0;
        if (m_horizontalBorder && m_verticalBorder)
        {
            m_horizontalBorder->draw(m_rect.getXPos() + m_verticalBorder->getWidth(), m_rect.getYPos(), 0, 0,
                                   m_rect.getWidth() - 2 * m_verticalBorder->getWidth(), m_horizontalBorder->getHeight());
            m_horizontalBorder->draw(m_rect.getXPos() + m_verticalBorder->getWidth(), m_rect.getYPos() + m_rect.getHeight() - m_horizontalBorder->getHeight(), 0, 0,
                                   m_rect.getWidth() - 2 * m_verticalBorder->getWidth(), m_horizontalBorder->getHeight());
            m_verticalBorder->draw(m_rect.getXPos(), m_rect.getYPos(), 0, 0,
                                 m_verticalBorder->getWidth(), m_rect.getHeight());
            m_verticalBorder->draw(m_rect.getXPos() + m_rect.getWidth() - m_verticalBorder->getWidth(), m_rect.getYPos(), 0, 0,
                                 m_verticalBorder->getWidth(), m_rect.getHeight());
            xoff = m_verticalBorder->getWidth();
            yoff = m_horizontalBorder->getHeight();
        }
        Image *portait = m_playerCharacter->getPortraitImage();
        if (portait)
        {
            portait->draw(m_rect.getXPos() +xoff, m_rect.getYPos() + yoff, 0);
        }
    }
}

void
PortraitWidget::drag(const int, const int)
{}

void
PortraitWidget::drop(const int, const int)
{}
