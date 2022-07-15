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

#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>

const unsigned int REPAIRABLE_MASK = 0x0020;
const unsigned int EQUIPED_MASK    = 0x0040;

class InventoryItem
{
protected:
    unsigned int m_id;
    unsigned int m_value;
    unsigned int m_flags;
public:
    InventoryItem ( const unsigned int i, const unsigned int v, const unsigned int f );
    InventoryItem ( const InventoryItem &item );
    virtual ~InventoryItem();
    unsigned int getId() const;
    unsigned int getValue() const;
    unsigned int getFlags() const;
    bool isEquiped() const;
    void equip ( const bool toggle );
    virtual const std::string toString() const = 0;
    InventoryItem& operator= ( const InventoryItem &item );
};

class SingleInventoryItem
    : public InventoryItem
{
public:
    SingleInventoryItem ( const unsigned int i );
    virtual ~SingleInventoryItem();
    const std::string toString() const;
    bool operator== ( const SingleInventoryItem &item ) const;
    bool operator!= ( const SingleInventoryItem &item ) const;
};

class MultipleInventoryItem
    : public InventoryItem
{
public:
    MultipleInventoryItem ( const unsigned int i, const unsigned int n );
    virtual ~MultipleInventoryItem();
    unsigned int getAmount() const;
    void add ( const unsigned int n );
    void remove ( const unsigned int n );
    const std::string toString() const;
    bool operator== ( const MultipleInventoryItem &item ) const;
    bool operator!= ( const MultipleInventoryItem &item ) const;
};

class RepairableInventoryItem
    : public InventoryItem
{
public:
    RepairableInventoryItem ( const unsigned int i, const unsigned int c );
    virtual ~RepairableInventoryItem();
    unsigned int getCondition() const;
    void repair ( const unsigned int n );
    void damage ( const unsigned int n );
    const std::string toString() const;
    bool operator== ( const RepairableInventoryItem &item ) const;
    bool operator!= ( const RepairableInventoryItem &item ) const;
};

class UsableInventoryItem
    : public InventoryItem
{
public:
    UsableInventoryItem ( const unsigned int i, const unsigned int u );
    virtual ~UsableInventoryItem();
    unsigned int getUses() const;
    void use ( const unsigned int n );
    void restore ( const unsigned int n );
    const std::string toString() const;
    bool operator== ( const UsableInventoryItem &item ) const;
    bool operator!= ( const UsableInventoryItem &item ) const;
};

#endif
