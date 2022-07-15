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
#include "inventory.h"
#include "objectresource.h"

Inventory::Inventory()
    : m_items()
{}

Inventory::~Inventory()
{
    for (std::list<InventoryData>::iterator it = m_items.begin(); it != m_items.end(); ++it)
    {
        delete it->m_item;
    }
    m_items.clear();
}

unsigned int
Inventory::getSize() const
{
    return m_items.size();
}

InventoryItem *
Inventory::getItem(const unsigned int n) const
{
    std::list<InventoryData>::const_iterator it = m_items.begin();
    for (unsigned int i = 0; i < n; i++) ++it;
    return it->m_item;
}

std::list<InventoryData>::iterator
Inventory::find(SingleInventoryItem* item)
{
    std::list<InventoryData>::iterator it = m_items.begin();
    while (it != m_items.end())
    {
        SingleInventoryItem *sii = dynamic_cast<SingleInventoryItem *>(it->m_item);
        if (sii && (*sii == *item))
        {
            break;
        }
        ++it;
    }
    return it;
}

std::list<InventoryData>::iterator
Inventory::find(MultipleInventoryItem* item)
{
    std::list<InventoryData>::iterator it = m_items.begin();
    while (it != m_items.end())
    {
        MultipleInventoryItem *mii = dynamic_cast<MultipleInventoryItem *>(it->m_item);
        if (mii && (*mii == *item))
        {
            break;
        }
        ++it;
    }
    return it;
}

std::list<InventoryData>::iterator
Inventory::find(RepairableInventoryItem* item)
{
    std::list<InventoryData>::iterator it = m_items.begin();
    while (it != m_items.end())
    {
        RepairableInventoryItem *rii = dynamic_cast<RepairableInventoryItem *>(it->m_item);
        if (rii && (*rii == *item))
        {
            break;
        }
        ++it;
    }
    return it;
}

std::list<InventoryData>::iterator
Inventory::find(UsableInventoryItem* item)
{
    std::list<InventoryData>::iterator it = m_items.begin();
    while (it != m_items.end())
    {
        UsableInventoryItem *uii = dynamic_cast<UsableInventoryItem *>(it->m_item);
        if (uii && (*uii == *item))
        {
            break;
        }
        ++it;
    }
    return it;
}

void
Inventory::add(InventoryItem* item)
{
    SingleInventoryItem *sii = dynamic_cast<SingleInventoryItem *>(item);
    if (sii)
    {
        add(sii);
        return;
    }
    MultipleInventoryItem *mii = dynamic_cast<MultipleInventoryItem *>(item);
    if (mii)
    {
        add(mii);
        return;
    }
    RepairableInventoryItem *rii = dynamic_cast<RepairableInventoryItem *>(item);
    if (rii)
    {
        add(rii);
        return;
    }
    UsableInventoryItem *uii = dynamic_cast<UsableInventoryItem *>(item);
    if (uii)
    {
        add(uii);
        return;
    }
}

void
Inventory::remove(InventoryItem* item)
{
    SingleInventoryItem *sii = dynamic_cast<SingleInventoryItem *>(item);
    if (sii)
    {
        remove(sii);
        return;
    }
    MultipleInventoryItem *mii = dynamic_cast<MultipleInventoryItem *>(item);
    if (mii)
    {
        remove(mii);
        return;
    }
    RepairableInventoryItem *rii = dynamic_cast<RepairableInventoryItem *>(item);
    if (rii)
    {
        remove(rii);
        return;
    }
    UsableInventoryItem *uii = dynamic_cast<UsableInventoryItem *>(item);
    if (uii)
    {
        remove(uii);
        return;
    }
}

void
Inventory::add(SingleInventoryItem* item)
{
    m_items.push_back(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
    m_items.sort();
    notify();
}

void
Inventory::remove(SingleInventoryItem* item)
{
    m_items.remove(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
    notify();
}

void
Inventory::add(MultipleInventoryItem* item)
{
    std::list<InventoryData>::iterator it = find(item);
    if (it != m_items.end())
    {
        MultipleInventoryItem *mii = dynamic_cast<MultipleInventoryItem *>(it->m_item);
        mii->add(item->getValue());
        delete item;
    }
    else
    {
        m_items.push_back(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
        m_items.sort();
    }
    notify();
}

void
Inventory::remove(MultipleInventoryItem* item)
{
    std::list<InventoryData>::iterator it = find(item);
    if (it != m_items.end())
    {
        MultipleInventoryItem *mii = dynamic_cast<MultipleInventoryItem *>(it->m_item);
        if (mii->getAmount() == item->getAmount())
        {
            m_items.remove(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
        }
        else
        {
            mii->remove(item->getAmount());
        }
    }
    else
    {
        throw UnexpectedValue(__FILE__, __LINE__, "m_items.end()");
    }
    notify();
}

void
Inventory::add(RepairableInventoryItem* item)
{
    m_items.push_back(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
    m_items.sort();
    notify();
}

void
Inventory::remove(RepairableInventoryItem* item)
{
    m_items.remove(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
    notify();
}

void
Inventory::add(UsableInventoryItem* item)
{
    m_items.push_back(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
    m_items.sort();
    notify();
}

void
Inventory::remove(UsableInventoryItem* item)
{
    m_items.remove(InventoryData(ObjectResource::getInstance()->getObjectInfo(item->getId()).imageSize, item));
    notify();
}
