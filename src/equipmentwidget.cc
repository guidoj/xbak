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

#include "equipmentwidget.h"
#include "exception.h"
#include "objectresource.h"
#include "widgetfactory.h"

const unsigned int ARMOR_OFFSET    = 60;
const unsigned int CROSSBOW_OFFSET = 30;

EquipmentWidget::EquipmentWidget(const Rectangle &r, PlayerCharacter *pc, ImageResource& img, Image *as, Image *cbs, Font *f)
    : ContainerWidget(r)
    , Observer()
    , m_character(pc)
    , m_images(img)
    , m_armorSlot(as)
    , m_crossbowSlot(cbs)
    , m_font(f)
{
    m_character->attach(this);
    m_character->getInventory()->attach(this);
    update();
}

EquipmentWidget::~EquipmentWidget()
{
    m_character->getInventory()->detach(this);
    m_character->detach(this);
}

void
EquipmentWidget::update()
{
    clear();
    WidgetFactory wf;
    bool armorEquipped = false;
    bool crossbowEquipped = false;
    for (unsigned int i = 0; i < m_character->getInventory()->getSize(); i++)
    {
        InventoryItem *item = m_character->getInventory()->getItem(i);
        if ((item->isEquiped()))
        {
            Image *image = m_images.getImage(item->getId());
            int width;
            int height;
            int yoffset;
            ObjectInfo objInfo = ObjectResource::getInstance()->getObjectInfo(item->getId());
            switch (objInfo.imageSize)
            {
            case 1:
                width = MAX_EQUIPMENT_ITEM_WIDGET_WIDTH / 2;
                height = MAX_EQUIPMENT_ITEM_WIDGET_HEIGHT / 2;
                break;
            case 2:
                width = MAX_EQUIPMENT_ITEM_WIDGET_WIDTH;
                height = MAX_EQUIPMENT_ITEM_WIDGET_HEIGHT / 2;
                break;
            case 4:
                width = MAX_EQUIPMENT_ITEM_WIDGET_WIDTH;
                height = MAX_EQUIPMENT_ITEM_WIDGET_HEIGHT;
                break;
            default:
                throw UnexpectedValue(__FILE__, __LINE__, objInfo.imageSize);
                break;
            }
            switch (objInfo.type)
            {
            case OT_SWORD:
                yoffset = 0;
                break;
            case OT_CROSSBOW:
                yoffset = CROSSBOW_OFFSET;
                crossbowEquipped = true;
                break;
            case OT_STAFF:
                yoffset = 0;
                break;
            case OT_ARMOR:
                yoffset = ARMOR_OFFSET;
                armorEquipped = true;
                break;
            default:
                throw UnexpectedValue(__FILE__, __LINE__, objInfo.type);
                break;
            }
            EquipmentItemWidget *eqitem = wf.createEquipmentItem(Rectangle(m_rect.getXPos() + 1, m_rect.getYPos() + yoffset + 1, width, height),
                                          objInfo.type, item, image, item->toString(), m_font);
            addWidget(eqitem);
        }
    }
    if (!armorEquipped)
    {
        EquipmentItemWidget *eqitem = wf.createEquipmentItem(Rectangle(m_rect.getXPos() + 1, m_rect.getYPos() + ARMOR_OFFSET + 1,
                                      MAX_EQUIPMENT_ITEM_WIDGET_WIDTH, MAX_EQUIPMENT_ITEM_WIDGET_HEIGHT),
                                      OT_ARMOR, 0, m_armorSlot, "", m_font);
        addWidget(eqitem);
    }
    if ((m_character->getCharacterClass() == CLASS_WARRIOR) && (!crossbowEquipped))
    {
        EquipmentItemWidget *eqitem = wf.createEquipmentItem(Rectangle(m_rect.getXPos() + 1, m_rect.getYPos() + CROSSBOW_OFFSET + 1,
                                      MAX_EQUIPMENT_ITEM_WIDGET_WIDTH, MAX_EQUIPMENT_ITEM_WIDGET_HEIGHT / 2),
                                      OT_CROSSBOW, 0, m_crossbowSlot, "", m_font);
        addWidget(eqitem);
    }
    setVisible(m_character->isSelected());
}
