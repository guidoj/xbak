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

#ifndef PARTY_RESOURCE_H
#define PARTY_RESOURCE_H

#include <vector>

#include "resourcedata.h"

const unsigned int PARTY_LOCKLEAR = 0;
const unsigned int PARTY_GORATH   = 1;
const unsigned int PARTY_OWYN     = 2;
const unsigned int PARTY_PUG      = 3;
const unsigned int PARTY_JAMES    = 4;
const unsigned int PARTY_PATRUS   = 5;
const unsigned int PARTY_SIZE     = 6;

struct PartyData
{
    std::string name;
};

class PartyResource
    : public ResourceData
{
private:
    std::vector<PartyData *> m_data;
public:
    PartyResource();
    virtual ~PartyResource();
    unsigned int getSize() const;
    PartyData* getData ( const unsigned int n );
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif

