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

#ifndef INVENTORY_H
#define INVENTORY_H

#include "inventoryitem.h"
#include "subject.h"

class InventoryData
{
public:
    unsigned int m_size;
    InventoryItem *m_item;
    InventoryData ( unsigned int n, InventoryItem *ii ) : m_size ( n ), m_item ( ii )
    {};
    bool operator== ( const InventoryData &invdata ) const
    {
        return ( invdata.m_size == m_size ) && ( invdata.m_item == m_item );
    };
    bool operator< ( const InventoryData &invdata ) const
    {
        return invdata.m_size < m_size;
    };
};

class Inventory
    : public Subject
{
private:
    std::list<InventoryData> m_items;
    std::list<InventoryData>::iterator find ( SingleInventoryItem* item );
    std::list<InventoryData>::iterator find ( MultipleInventoryItem* item );
    std::list<InventoryData>::iterator find ( RepairableInventoryItem* item );
    std::list<InventoryData>::iterator find ( UsableInventoryItem* item );
public:
    Inventory();
    virtual ~Inventory();
    unsigned int getSize() const;
    InventoryItem* getItem ( const unsigned int n ) const;
    void add ( InventoryItem *item );
    void remove ( InventoryItem *item );
    void add ( SingleInventoryItem *item );
    void remove ( SingleInventoryItem *item );
    void add ( MultipleInventoryItem *item );
    void remove ( MultipleInventoryItem *item );
    void add ( RepairableInventoryItem *item );
    void remove ( RepairableInventoryItem *item );
    void add ( UsableInventoryItem *item );
    void remove ( UsableInventoryItem *item );
};

#endif
