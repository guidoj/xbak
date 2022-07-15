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

#include <sstream>

#include "inventoryitem.h"

InventoryItem::InventoryItem(const unsigned int i, const unsigned int v, const unsigned int f)
    : m_id(i)
    , m_value(v)
    , m_flags(f)
{}

InventoryItem::InventoryItem(const InventoryItem &item)
    : m_id(item.m_id)
    , m_value(item.m_value)
    , m_flags(item.m_flags)
{}

InventoryItem::~InventoryItem()
{}

unsigned int
InventoryItem::getId() const
{
    return m_id;
}

unsigned int
InventoryItem::getValue() const
{
    return m_value;
}

unsigned int
InventoryItem::getFlags() const
{
    return m_flags;
}

bool
InventoryItem::isEquiped() const
{
    return m_flags & EQUIPED_MASK;
}

void
InventoryItem::equip(const bool toggle)
{
    if (toggle)
    {
        m_flags |= EQUIPED_MASK;
    }
    else
    {
        m_flags &= ~EQUIPED_MASK;
    }
}

InventoryItem &
InventoryItem::operator=(const InventoryItem &item)
{
    m_id = item.m_id;
    m_value = item.m_value;
    m_flags = item.m_flags;
    return *this;
}


SingleInventoryItem::SingleInventoryItem(const unsigned int i)
    : InventoryItem(i, 0, 0)
{}

SingleInventoryItem::~SingleInventoryItem()
{}

const std::string
SingleInventoryItem::toString() const
{
    return "";
}

bool
SingleInventoryItem::operator==(const SingleInventoryItem &) const
{
    return false;
}

bool
SingleInventoryItem::operator!=(const SingleInventoryItem &) const
{
    return true;
}


MultipleInventoryItem::MultipleInventoryItem(const unsigned int i, const unsigned int n)
    : InventoryItem(i, n, 0)
{}

MultipleInventoryItem::~MultipleInventoryItem()
{}

unsigned int
MultipleInventoryItem::getAmount() const
{
    return m_value;
}

void
MultipleInventoryItem::add(const unsigned int n)
{
    m_value += n;
}

void
MultipleInventoryItem::remove(const unsigned int n)
{
    m_value -= n;
}

const std::string
MultipleInventoryItem::toString() const
{
    std::stringstream ss;
    ss << m_value;
    return ss.str();
}

bool
MultipleInventoryItem::operator==(const MultipleInventoryItem &item) const
{
    return (m_id == item.m_id);
}

bool
MultipleInventoryItem::operator!=(const MultipleInventoryItem &item) const
{
    return (m_id != item.m_id);
}


RepairableInventoryItem::RepairableInventoryItem(const unsigned int i, const unsigned int c)
    : InventoryItem(i, c, REPAIRABLE_MASK)
{}

RepairableInventoryItem::~RepairableInventoryItem()
{}

void
RepairableInventoryItem::repair(const unsigned int n)
{
    m_value += n;
}

void
RepairableInventoryItem::damage(const unsigned int n)
{
    m_value -= n;
}

const std::string
RepairableInventoryItem::toString() const
{
    std::stringstream ss;
    ss << m_value << "%";
    return ss.str();
}

bool
RepairableInventoryItem::operator==(const RepairableInventoryItem &) const
{
    return false;
}

bool
RepairableInventoryItem::operator!=(const RepairableInventoryItem &) const
{
    return true;
}


UsableInventoryItem::UsableInventoryItem(const unsigned int i, const unsigned int u)
    : InventoryItem(i, u, 0)
{}

UsableInventoryItem::~UsableInventoryItem()
{}

void
UsableInventoryItem::use(const unsigned int n)
{
    m_value += n;
}

void
UsableInventoryItem::restore(const unsigned int n)
{
    m_value -= n;
}

const std::string
UsableInventoryItem::toString() const
{
    return "";
}

bool
UsableInventoryItem::operator==(const UsableInventoryItem &) const
{
    return false;
}

bool
UsableInventoryItem::operator!=(const UsableInventoryItem &) const
{
    return true;
}
