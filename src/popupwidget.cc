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
#include "popupwidget.h"

PopUpWidget::PopUpWidget ( const Rectangle &r )
    : ContainerWidget ( r )
{
}

PopUpWidget::~PopUpWidget()
{
}

void
PopUpWidget::draw()
{
    if ( isVisible() )
    {
        Video *video = MediaToolkit::getInstance()->getVideo();
        video->fillRect ( m_rect.getXPos() + 1, m_rect.getYPos() + 1, m_rect.getWidth() - 2, m_rect.getHeight() - 2, POPUP_COLOR );
        video->drawVLine ( m_rect.getXPos(), m_rect.getYPos(), m_rect.getHeight(), SHADOW_COLOR );
        video->drawHLine ( m_rect.getXPos() + 1, m_rect.getYPos(), m_rect.getWidth() - 1, LIGHT_COLOR );
        video->drawVLine ( m_rect.getXPos() + m_rect.getWidth() - 1, m_rect.getYPos() + 1, m_rect.getHeight() - 2, LIGHT_COLOR );
        video->drawHLine ( m_rect.getXPos() + 1, m_rect.getYPos() + m_rect.getHeight() - 1, m_rect.getWidth() - 1, SHADOW_COLOR );
        video->drawVLine ( m_rect.getXPos() - 1, m_rect.getYPos() + 1, m_rect.getHeight(), COLOR_BLACK );
        video->drawHLine ( m_rect.getXPos(), m_rect.getYPos() + m_rect.getHeight(), m_rect.getWidth() - 1, COLOR_BLACK );
        DrawChildWidgets();
    }
}
