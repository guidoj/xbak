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

#ifndef PARTY_H
#define PARTY_H

#include "orientation.h"
#include "playercharacter.h"

class Party
{
private:
    std::vector<PlayerCharacter *> m_members;
    unsigned int m_numActiveMembers;
public:
    Party();
    ~Party();
    unsigned int getNumMembers() const;
    PlayerCharacter* getMember ( const unsigned int n );
    void addMember ( PlayerCharacter *pc );
    unsigned int getNumActiveMembers() const;
    PlayerCharacter* getActiveMember ( const int order );
    unsigned int getActiveMemberIndex ( const int order ) const;
    void activateMember ( const unsigned int n, const int order );
    PlayerCharacter* getSelectedMember();
    void selectMember ( const int order );
};

#endif

