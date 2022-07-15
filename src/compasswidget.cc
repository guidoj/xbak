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

#include "compasswidget.h"

const int COMPASS_WIDGET_XPOS   = 144;
const int COMPASS_WIDGET_YPOS   = 121;
const int COMPASS_WIDGET_WIDTH  = 32;
const int COMPASS_WIDGET_HEIGHT = 11;

const Rectangle COMPASS_WIDGET_RECTANGLE = Rectangle(COMPASS_WIDGET_XPOS, COMPASS_WIDGET_YPOS, COMPASS_WIDGET_WIDTH, COMPASS_WIDGET_HEIGHT);

CompassWidget::CompassWidget(Camera *cam, Image *img)
    : Widget(COMPASS_WIDGET_RECTANGLE)
    , m_camera(cam)
    , m_compassImage(img)
    , m_cachedImage(0)
{
    m_cachedImage = new Image(COMPASS_WIDGET_WIDTH, COMPASS_WIDGET_HEIGHT);
    m_camera->attach(this);
    update();
}

CompassWidget::~CompassWidget()
{
    m_camera->detach(this);
    if (m_cachedImage)
    {
        delete m_cachedImage;
    }
}

void CompassWidget::draw()
{
    if (isVisible())
    {
        if (m_cachedImage)
        {
            m_cachedImage->draw(m_rect.getXPos(), m_rect.getYPos());
        }
    }
}

void CompassWidget::update()
{
    if (m_compassImage)
    {
        int offset = m_camera->getHeading();
        int imagewidth = m_compassImage->getWidth();
        m_compassImage->draw(m_rect.getXPos() - offset, m_rect.getYPos(), offset, 0, m_rect.getWidth(), m_rect.getHeight());
        if ((imagewidth - offset) < m_rect.getWidth())
        {
            m_compassImage->draw(m_rect.getXPos() - offset + imagewidth, m_rect.getYPos(), 0, 0, m_rect.getWidth() - imagewidth + offset, m_rect.getHeight());
        }
    }
    if (m_cachedImage)
    {
        m_cachedImage->read(m_rect.getXPos(), m_rect.getYPos());
    }
}

void CompassWidget::drag(const int, const int)
{
}

void CompassWidget::drop(const int, const int)
{
}
