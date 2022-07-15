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

#include "imagewidget.h"

ImageWidget::ImageWidget(const Rectangle &r, Image *img)
    : Widget(r)
    , m_image(0)
{
    m_image = new Image(img);
}

ImageWidget::~ImageWidget()
{
    delete m_image;
}

void
ImageWidget::horizontalFlip()
{
    m_image->horizontalFlip();
}

void
ImageWidget::verticalFlip()
{
    m_image->verticalFlip();
}

void
ImageWidget::draw()
{
    if (isVisible())
    {
        m_image->draw(m_rect.getXPos(), m_rect.getYPos(), 0, 0, m_rect.getWidth(), m_rect.getHeight(), 0);
    }
}

void
ImageWidget::drag(const int, const int)
{}

void
ImageWidget::drop(const int, const int)
{}
