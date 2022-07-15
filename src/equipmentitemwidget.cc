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

#include "equipmentitemwidget.h"
#include "exception.h"
#include "pointermanager.h"

EquipmentItemWidget::EquipmentItemWidget(const Rectangle &r, const ObjectType t)
    : Widget(r)
    , m_type(t)
    , m_invItem(0)
    , m_iconImage(0)
    , m_label(0)
{}

EquipmentItemWidget::~EquipmentItemWidget()
{
    if (m_label)
    {
        delete m_label;
    }
}

void
EquipmentItemWidget::setImage(Image *icon)
{
    if (!icon)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_iconImage = icon;
}

InventoryItem*
EquipmentItemWidget::getInventoryItem()
{
    return m_invItem;
}

void
EquipmentItemWidget::setInventoryItem(InventoryItem *item)
{
    m_invItem = item;
}

void
EquipmentItemWidget::setLabel(const std::string& s, Font *f)
{
    m_label = new TextWidget(Rectangle(m_rect.getXPos(), m_rect.getYPos(), m_rect.getWidth(), m_rect.getHeight()), f);
    m_label->setText(s);
    m_label->setColor(INFO_TEXT_COLOR);
    m_label->setAlignment(HA_RIGHT, VA_BOTTOM);
}

void
EquipmentItemWidget::draw()
{
    if (isVisible())
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

void
EquipmentItemWidget::drag(const int, const int)
{}

void
EquipmentItemWidget::drop(const int, const int)
{
    InventoryItemWidget *widget = PointerManager::getInstance()->getDraggedWidget();
    if (widget)
    {
        InventoryItem *item = widget->getInventoryItem();
        if (item)
        {
            ObjectInfo objInfo = ObjectResource::getInstance()->getObjectInfo(item->getId());
            if (m_type == objInfo.type)
            {
                m_invItem->equip(false);
                item->equip(true);
            }
        }
    }
}
