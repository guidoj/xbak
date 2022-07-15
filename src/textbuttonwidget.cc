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
#include "requestresource.h"
#include "textbuttonwidget.h"

TextButtonWidget::TextButtonWidget(const Rectangle &r, const int a)
    : ButtonWidget(r, a)
    , m_label(0)
{
}

TextButtonWidget::~TextButtonWidget()
{
    if (m_label)
    {
        delete m_label;
    }
}

void
TextButtonWidget::setLabel(const std::string& s, Font *f)
{
    m_label = new TextWidget(Rectangle(m_rect.getXPos() + 2, m_rect.getYPos() + 2, m_rect.getWidth() - 4, m_rect.getHeight() - 4), f);
    m_label->setText(s);
}

void
TextButtonWidget::draw()
{
    if (isVisible())
    {
        if (isPressed())
        {
            Video *video = MediaToolkit::getInstance()->getVideo();
            video->fillRect(m_rect.getXPos() + 1, m_rect.getYPos() + 1, m_rect.getWidth() - 2, m_rect.getHeight() - 2, BUTTON_COLOR_PRESSED);
            video->drawVLine(m_rect.getXPos(), m_rect.getYPos(), m_rect.getHeight(), LIGHT_COLOR);
            video->drawHLine(m_rect.getXPos() + 1, m_rect.getYPos(), m_rect.getWidth() - 1, SHADOW_COLOR);
            video->drawVLine(m_rect.getXPos() + m_rect.getWidth() - 1, m_rect.getYPos() + 1, m_rect.getHeight() - 2, SHADOW_COLOR);
            video->drawHLine(m_rect.getXPos() + 1, m_rect.getYPos() + m_rect.getHeight() - 1, m_rect.getWidth() - 1, LIGHT_COLOR);
        }
        else
        {
            Video *video = MediaToolkit::getInstance()->getVideo();
            video->fillRect(m_rect.getXPos() + 1, m_rect.getYPos() + 1, m_rect.getWidth() - 2, m_rect.getHeight() - 2, BUTTON_COLOR_NORMAL);
            video->drawVLine(m_rect.getXPos(), m_rect.getYPos(), m_rect.getHeight(), SHADOW_COLOR);
            video->drawHLine(m_rect.getXPos() + 1, m_rect.getYPos(), m_rect.getWidth() - 1, LIGHT_COLOR);
            video->drawVLine(m_rect.getXPos() + m_rect.getWidth() - 1, m_rect.getYPos() + 1, m_rect.getHeight() - 2, LIGHT_COLOR);
            video->drawHLine(m_rect.getXPos() + 1, m_rect.getYPos() + m_rect.getHeight() - 1, m_rect.getWidth() - 1, SHADOW_COLOR);
        }
        if (m_label)
        {
            if (isEnabled())
            {
                if (isPressed())
                {
                    m_label->setColor(TEXT_COLOR_PRESSED);
                    m_label->setShadow(SHADOW_COLOR, 0, 1);
                }
                else
                {
                    m_label->setColor(TEXT_COLOR_NORMAL);
                    m_label->setShadow(SHADOW_COLOR, 0, 1);
                }
            }
            else
            {
                m_label->setColor(TEXT_COLOR_DISABLED);
                m_label->setShadow(NO_SHADOW, 0, 0);
            }
            m_label->draw();
        }
    }
}

void
TextButtonWidget::leftClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        setPressed(toggle);
        generateActionEvent(toggle ? getAction() : ACT_STOP);
    }
}

void
TextButtonWidget::rightClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        if (toggle)
        {
        }
    }
}
