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
#include "inventorywidget.h"
#include "widgetfactory.h"

InventoryWidget::InventoryWidget(const Rectangle &r, PlayerCharacter *pc, ImageResource& img, Font *f)
    : ActionEventListener()
    , ContainerWidget(r)
    , Observer()
    , m_character(pc)
    , m_images(img)
    , m_font(f)
    , m_freeSpaces()
{
    m_character->attach(this);
    m_character->getInventory()->attach(this);
    update();
}

InventoryWidget::~InventoryWidget()
{
    m_character->getInventory()->detach(this);
    m_character->detach(this);
}

void
InventoryWidget::actionPerformed(const ActionEvent &ae)
{
    generateActionEvent(ae);
}

void
InventoryWidget::update()
{
    clear();
    WidgetFactory wf;
    m_freeSpaces.push_back(m_rect);
    for (unsigned int i = 0; i < m_character->getInventory()->getSize(); i++)
    {
        InventoryItem *item = m_character->getInventory()->getItem(i);
        if (!(item->isEquiped()))
        {
            Image *image = m_images.getImage(item->getId());
            int width;
            int height;
            ObjectInfo objInfo = ObjectResource::getInstance()->getObjectInfo(item->getId());
            switch (objInfo.imageSize)
            {
            case 1:
                width = MAX_INVENTORY_ITEM_WIDGET_WIDTH / 2;
                height = MAX_INVENTORY_ITEM_WIDGET_HEIGHT / 2;
                break;
            case 2:
                width = MAX_INVENTORY_ITEM_WIDGET_WIDTH;
                height = MAX_INVENTORY_ITEM_WIDGET_HEIGHT / 2;
                break;
            case 4:
                width = MAX_INVENTORY_ITEM_WIDGET_WIDTH;
                height = MAX_INVENTORY_ITEM_WIDGET_HEIGHT;
                break;
            default:
                throw UnexpectedValue(__FILE__, __LINE__, objInfo.imageSize);
                break;
            }
            std::list<Rectangle>::iterator it = m_freeSpaces.begin();
            while (it != m_freeSpaces.end())
            {
                if ((it->getWidth() > width) && (it->getHeight() > height))
                {
                    InventoryItemWidget *invitem = wf.createInventoryItem(Rectangle(it->getXPos() + 1,
                                                   it->getYPos() + 1,
                                                   width,
                                                   height),
                                                   INVENTORY_OFFSET + i,
                                                   item,
                                                   image,
                                                   item->toString(),
                                                   m_font,
                                                   this);
                    addActiveWidget(invitem);
                    Rectangle origFreeSpace(*it);
                    m_freeSpaces.erase(it);
                    if ((origFreeSpace.getWidth() - width) > (MAX_INVENTORY_ITEM_WIDGET_WIDTH / 2))
                    {
                        m_freeSpaces.push_back(Rectangle(origFreeSpace.getXPos() + width + 1,
                                                       origFreeSpace.getYPos(),
                                                       origFreeSpace.getWidth() - width - 1,
                                                       origFreeSpace.getHeight()));
                    }
                    if ((origFreeSpace.getHeight() - height) > (MAX_INVENTORY_ITEM_WIDGET_HEIGHT / 2))
                    {
                        m_freeSpaces.push_back(Rectangle(origFreeSpace.getXPos(),
                                                       origFreeSpace.getYPos() + height + 1,
                                                       origFreeSpace.getWidth(),
                                                       origFreeSpace.getHeight() - height - 1));
                    }
                    m_freeSpaces.sort();
                    it = m_freeSpaces.end();
                }
                else
                {
                    ++it;
                }
            }
        }
    }
    m_freeSpaces.clear();
    setVisible(m_character->isSelected());
}
