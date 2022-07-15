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

#include "party.h"

Party::Party()
    : m_members()
    , m_numActiveMembers(0)
{}

Party::~Party()
{
    for (unsigned int i = 0; i < m_members.size(); i++)
    {
        delete m_members[i];
    }
    m_members.clear();
    m_numActiveMembers = 0;
}

unsigned int
Party::getNumMembers() const
{
    return m_members.size();
}

PlayerCharacter *
Party::getMember(const unsigned int n)
{
    return m_members[n];
}

unsigned int
Party::getNumActiveMembers() const
{
    return m_numActiveMembers;
}

PlayerCharacter *
Party::getActiveMember(const int order)
{
    unsigned int n = getActiveMemberIndex(order);
    if (n < m_members.size())
    {
        return m_members[n];
    }
    return 0;
}

unsigned int
Party::getActiveMemberIndex(const int order) const
{
    unsigned int i = 0;
    while (i < m_members.size())
    {
        if (order == m_members[i]->getOrder())
        {
            return i;
        }
        i++;
    }
    return m_members.size();
}

PlayerCharacter *
Party::getSelectedMember()
{
    unsigned int i = 0;
    while (i < m_members.size())
    {
        if (m_members[i]->isSelected())
        {
            return m_members[i];
        }
        i++;
    }
    return 0;
}

void
Party::addMember(PlayerCharacter *pc)
{
    m_members.push_back(pc);
}

void
Party::activateMember(const unsigned int n, const int order)
{
    PlayerCharacter *pc = getActiveMember(order);
    if (pc)
    {
        pc->setOrder(-1);
        m_numActiveMembers--;
    }
    if (m_members[n]->getOrder() >= 0)
    {
        m_numActiveMembers--;
    }
    m_members[n]->setOrder(order);
    m_numActiveMembers++;
}

void
Party::selectMember(const int order)
{
    for (unsigned int i = 0; i < m_members.size(); i++)
    {
        m_members[i]->select((order >= 0) && (m_members[i]->getOrder() == order));
    }
}
