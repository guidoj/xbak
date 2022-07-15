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
#include "imagebuttonwidget.h"
#include "requestresource.h"

ImageButtonWidget::ImageButtonWidget(const Rectangle &r, const int a)
    : ButtonWidget(r, a)
    , m_normalImage(0)
    , m_pressedImage(0)
{
}

ImageButtonWidget::~ImageButtonWidget()
{
}

void
ImageButtonWidget::setImage(Image *normal, Image *press)
{
    if ((!normal) || (!press))
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_normalImage = normal;
    m_pressedImage = press;
}

void
ImageButtonWidget::draw()
{
    if (isVisible())
    {
        if (isEnabled())
        {
            if (isPressed())
            {
                if (m_pressedImage)
                {
                    m_pressedImage->draw(m_rect.getXPos(), m_rect.getYPos() + 1, 0);
                }
            }
            else
            {
                if (m_normalImage)
                {
                    m_normalImage->draw(m_rect.getXPos(), m_rect.getYPos() + 1, 0);
                }
            }
        }
    }
}

void
ImageButtonWidget::leftClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        setPressed(toggle);
        generateActionEvent(toggle ? getAction() : ACT_STOP);
    }
}

void
ImageButtonWidget::rightClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        if (toggle)
        {
        }
    }
}
