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

#ifndef INVENTORY_ITEM_WIDGET_H
#define INVENTORY_ITEM_WIDGET_H

#include "image.h"
#include "inventoryitem.h"
#include "textwidget.h"

const int MAX_INVENTORY_ITEM_WIDGET_WIDTH  = 80;
const int MAX_INVENTORY_ITEM_WIDGET_HEIGHT = 58;

class InventoryItemWidget
    : public ActiveWidget
{
private:
    InventoryItem *m_invItem;
    Image *m_iconImage;
    TextWidget *m_label;
    bool m_dragged;
    bool m_selected;
public:
    InventoryItemWidget ( const Rectangle &r, const int a );
    virtual ~InventoryItemWidget();
    InventoryItem* getInventoryItem();
    void setInventoryItem ( InventoryItem *item );
    Image* getImage();
    void setImage ( Image *icon );
    void setLabel ( const std::string& s, Font *f );
    void setDragged( const bool toggle );
    void draw();
    void leftClick ( const bool toggle, const int x, const int y );
    void rightClick ( const bool toggle, const int x, const int y );
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
