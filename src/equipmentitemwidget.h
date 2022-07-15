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

#ifndef EQUIPMENT_ITEM_WIDGET_H
#define EQUIPMENT_ITEM_WIDGET_H

#include "image.h"
#include "inventoryitem.h"
#include "objectresource.h"
#include "textwidget.h"

const int MAX_EQUIPMENT_ITEM_WIDGET_WIDTH  = 80;
const int MAX_EQUIPMENT_ITEM_WIDGET_HEIGHT = 58;

class EquipmentItemWidget : public Widget
{
private:
    ObjectType m_type;
    InventoryItem *m_invItem;
    Image *m_iconImage;
    TextWidget *m_label;
public:
    EquipmentItemWidget ( const Rectangle &r, const ObjectType t );
    virtual ~EquipmentItemWidget();
    InventoryItem* getInventoryItem();
    void setInventoryItem ( InventoryItem *item );
    void setImage ( Image *icon );
    void setLabel ( const std::string& s, Font *f );
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
