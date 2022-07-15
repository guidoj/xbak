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
#include "gameresource.h"
#include "objectresource.h"

const unsigned int INVENTORY_SLOTS = 24;

GameResource::GameResource()
    : m_game(0)
    , m_xLoc(0)
    , m_yLoc(0)
{
}

GameResource::~GameResource()
{
    if (m_game)
    {
        delete m_game;
    }
}

Game * GameResource::getGame()
{
    return m_game;
}

void GameResource::setGame(Game *g)
{
    m_game = g;
}

unsigned int GameResource::getZone() const
{
    return m_zone;
}

void GameResource::setZone(const unsigned int z)
{
    m_zone = z;
}

unsigned int GameResource::getXLoc() const
{
    return m_xLoc;
}

void GameResource::setXLoc(const unsigned int x)
{
    m_xLoc = x;
}

unsigned int GameResource::getYLoc() const
{
    return m_yLoc;
}

void GameResource::setYLoc(const unsigned int y)
{
    m_yLoc = y;
}

void GameResource::load(FileBuffer *buffer)
{
    try
    {
        if (m_game)
        {
            delete m_game;
        }
        m_game = new Game();
        m_game->setName(buffer->getString());
        buffer->seek(0x00005a);
        buffer->skip(16);
        m_yLoc = buffer->getUint32LE();
        m_xLoc = buffer->getUint32LE();
        buffer->skip(4);
        m_zone = buffer->getUint8();
        int xcell = buffer->getUint8();
        int ycell = buffer->getUint8();
        int xpos = buffer->getUint32LE();
        int ypos = buffer->getUint32LE();
        m_game->getCamera()->setPosition(Vector2D(xpos, ypos));
        if (m_game->getCamera()->getPosition().getCell() != Vector2D(xcell, ycell))
        {
            throw DataCorruption(__FILE__, __LINE__, "cell != position");
        }
        buffer->skip(5);
        m_game->getCamera()->setHeading(buffer->getUint16LE());
        buffer->skip(23);
        for (unsigned int m = 0; m < m_game->getParty()->getNumMembers(); m++)
        {
            m_game->getParty()->getMember(m)->setName(buffer->getString(10));
        }
        for (unsigned int m = 0; m < m_game->getParty()->getNumMembers(); m++)
        {
            buffer->skip(8);
            for (unsigned int i = 0; i < NUM_STATS; i++)
            {
                for (unsigned int j = 0; j < NUM_STAT_VALUES; j++)
                {
                    m_game->getParty()->getMember(m)->getStatistics().set(i, j, buffer->getUint8());
                }
            }
            if (m_game->getParty()->getMember(m)->getStatistics().get(STAT_CROSSBOW_ACCURACY, STAT_MAXIMUM) > 0)
            {
                m_game->getParty()->getMember(m)->setCharacterClass(CLASS_WARRIOR);
            }
            if (m_game->getParty()->getMember(m)->getStatistics().get(STAT_CASTING_ACCURACY, STAT_MAXIMUM) > 0)
            {
                m_game->getParty()->getMember(m)->setCharacterClass(CLASS_SPELLCASTER);
            }
            buffer->skip(7);
        }
        unsigned int n = buffer->getUint8();
        for (unsigned int i = 0; i < n; i++)
        {
            m_game->getParty()->activateMember(buffer->getUint8(), i);
        }
        if (m_game->getParty()->getNumActiveMembers() != n)
        {
            throw DataCorruption(__FILE__, __LINE__, "active members");
        }
        buffer->seek(0x03a7f8);
        for (unsigned int m = 0; m < m_game->getParty()->getNumMembers(); m++)
        {
            buffer->skip(buffer->getUint16LE());
            unsigned int numItems = buffer->getUint8();
            unsigned int numSlots = buffer->getUint16LE();
            if (numSlots != INVENTORY_SLOTS)
            {
                throw DataCorruption(__FILE__, __LINE__, "inventory slots");
            }
            Inventory *inv = m_game->getParty()->getMember(m)->getInventory();
            for (unsigned int i = 0; i < numSlots; i++)
            {
                if (i < numItems)
                {
                    unsigned int id = buffer->getUint8();
                    unsigned int value = buffer->getUint8();
                    unsigned int flags = buffer->getUint16LE();
                    switch (ObjectResource::getInstance()->getObjectInfo(id).type)
                    {
                    case OT_SWORD:
                    case OT_CROSSBOW:
                    case OT_ARMOR:
                    {
                        RepairableInventoryItem *item = new RepairableInventoryItem(id, value);
                        item->equip(flags & EQUIPED_MASK);
                        inv->add(item);
                    }
                    break;
                    case OT_STAFF:
                    {
                        SingleInventoryItem *item = new SingleInventoryItem(id);
                        item->equip(flags & EQUIPED_MASK);
                        inv->add(item);
                    }
                    break;
                    case OT_WEAPON_OIL:
                    case OT_ARMOR_OIL:
                    case OT_SPECIAL_OIL:
                    case OT_BOWSTRING:
                    case OT_SCROLL:
                    case OT_NOTE:
                    case OT_BOOK:
                    case OT_POTION:
                    case OT_RESTORATIVES:
                    case OT_CONTAINER:
                    case OT_LIGHTER:
                    case OT_INGREDIENT:
                    {
                        UsableInventoryItem *item = new UsableInventoryItem(id, value);
                        inv->add(item);
                    }
                    break;
                    case OT_UNSPECIFIED:
                    case OT_KEY:
                    case OT_TOOL:
                    case OT_RATION:
                    case OT_FOOD:
                    {
                        MultipleInventoryItem *item = new MultipleInventoryItem(id, value);
                        inv->add(item);
                    }
                    break;
                    case OT_UNKNOWN5:
                    case OT_UNKNOWN6:
                    case OT_UNKNOWN14:
                    case OT_UNKNOWN15:
                        throw DataCorruption(__FILE__, __LINE__, "unknown object type: ", ObjectResource::getInstance()->getObjectInfo(id).type);
                        break;
                    default:
                        throw DataCorruption(__FILE__, __LINE__, "invalid object type: ", ObjectResource::getInstance()->getObjectInfo(id).type);
                        break;
                    }
                }
                else
                {
                    buffer->skip(4);
                }
            }
            buffer->skip(1);
        }
    }
    catch (Exception &e)
    {
        e.print("GameResource::Load");
        throw;
    }
}

unsigned int GameResource::save(FileBuffer *buffer)
{
    if (!m_game)
    {
        throw NullPointer(__FILE__, __LINE__, "game");
    }
    try
    {
        buffer->rewind();
        buffer->putString(m_game->getName());
        buffer->seek(0x00005a);
        buffer->skip(16);
        buffer->putUint32LE(m_yLoc);
        buffer->putUint32LE(m_xLoc);
        buffer->skip(4);
        buffer->putUint8(m_zone);
        buffer->putUint8(m_game->getCamera()->getPosition().getCell().getX());
        buffer->putUint8(m_game->getCamera()->getPosition().getCell().getY());
        buffer->putUint32LE(m_game->getCamera()->getPos().getX());
        buffer->putUint32LE(m_game->getCamera()->getPos().getY());
        buffer->skip(5);
        buffer->putUint16LE(m_game->getCamera()->getHeading());
        buffer->skip(23);
        for (unsigned int m = 0; m < m_game->getParty()->getNumMembers(); m++)
        {
            buffer->putString(m_game->getParty()->getMember(m)->getName(), 10);
        }
        for (unsigned int m = 0; m < m_game->getParty()->getNumMembers(); m++)
        {
            buffer->skip(8);
            for (unsigned int i = 0; i < NUM_STATS; i++)
            {
                for (unsigned int j = 0; j < NUM_STAT_VALUES; j++)
                {
                    buffer->putUint8(m_game->getParty()->getMember(m)->getStatistics().get(i, j));
                }
            }
            buffer->putUint8(m + 1);
            buffer->skip(6);
        }
        buffer->putUint8(m_game->getParty()->getNumActiveMembers());
        for (unsigned int i = 0; i < m_game->getParty()->getNumActiveMembers(); i++)
        {
            buffer->putUint8(m_game->getParty()->getActiveMemberIndex(i));
        }
        buffer->seek(0x03a7f8);
        for (unsigned int m = 0; m < m_game->getParty()->getNumMembers(); m++)
        {
            buffer->skip(12);
            Inventory *inv = m_game->getParty()->getMember(m)->getInventory();
            buffer->putUint8(inv->getSize());
            buffer->putUint8(INVENTORY_SLOTS);
            for (unsigned int i = 0; i < INVENTORY_SLOTS; i++)
            {
                if (i < inv->getSize())
                {
                    const InventoryItem *item = inv->getItem(i);
                    buffer->putUint8(item->getId());
                    buffer->putUint8(item->getValue());
                    buffer->putUint16LE(item->getFlags());
                }
                else
                {
                    buffer->putUint32LE(0);
                }
            }
        }
        return buffer->getSize();
    }
    catch (Exception &e)
    {
        e.print("GameResource::Save");
        throw;
    }
}
