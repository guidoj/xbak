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
#include "inventoryitemwidget.h"
#include "pointermanager.h"
#include "requestresource.h"

InventoryItemWidget::InventoryItemWidget(const Rectangle &r, const int a)
    : ActiveWidget(r, a)
    , m_invItem(0)
    , m_iconImage(0)
    , m_label(0)
    , m_dragged(false)
    , m_selected(false)
{
    setFocusable(false);
}

InventoryItemWidget::~InventoryItemWidget()
{
    if (m_label)
    {
        delete m_label;
    }
}

InventoryItem*
InventoryItemWidget::getInventoryItem()
{
    return m_invItem;
}

void
InventoryItemWidget::setInventoryItem(InventoryItem *item)
{
    if (!item)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_invItem = item;
}

Image*
InventoryItemWidget::getImage()
{
    return m_iconImage;
}

void
InventoryItemWidget::setImage(Image *icon)
{
    if (!icon)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_iconImage = icon;
}

void
InventoryItemWidget::setLabel(const std::string& s, Font *f)
{
    m_label = new TextWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos(), m_rect.getWidth(), m_rect.getHeight()), f);
    m_label->setText(s);
    m_label->setColor(INFO_TEXT_COLOR);
    m_label->setAlignment(HA_RIGHT, VA_BOTTOM);
}

void
InventoryItemWidget::setDragged(const bool toggle)
{
    m_dragged = toggle;
}

void
InventoryItemWidget::draw()
{
    if (isVisible())
    {
        if (m_selected)
        {
        }
        if (!m_dragged)
        {
            if (m_iconImage)
            {
                m_iconImage->draw(m_rect.getXPos() + (m_rect.getWidth() - m_iconImage->getWidth()) / 2,
                                m_rect.getYPos() + (m_rect.getHeight() - m_iconImage->getHeight()) / 2, 0);
            }
            if (m_label)
            {
                m_label->draw();
            }
        }
    }
}

void
InventoryItemWidget::leftClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        generateActionEvent(toggle ? getAction() : ACT_STOP);
    }
}

void
InventoryItemWidget::rightClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        m_selected = toggle;
        generateActionEvent(toggle ? (getAction() + RIGHT_CLICK_OFFSET) : ACT_STOP);
    }
}

void
InventoryItemWidget::drag(const int x, const int y)
{
    m_dragged = true;
    PointerManager::getInstance()->setDraggedWidget(this,
            m_rect.getXPos() + (m_rect.getWidth() - m_iconImage->getWidth()) / 2 - x,
            m_rect.getYPos() + (m_rect.getHeight() - m_iconImage->getHeight()) / 2 - y);
}

void
InventoryItemWidget::drop(const int, const int)
{
}
