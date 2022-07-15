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

#include <cstring>

#include "exception.h"
#include "statistics.h"

Statistics::Statistics()
{
    memset(m_statMatrix, 0, sizeof(m_statMatrix));
}

Statistics::~Statistics()
{}

int
Statistics::get(const unsigned int stat, const unsigned int type) const
{
    if ((stat < NUM_STATS) && (type < NUM_STAT_VALUES))
    {
        return m_statMatrix[stat][type];
    }
    else
    {
        throw IndexOutOfRange(__FILE__, __LINE__, "statMatrix");
    }
}

void
Statistics::set(const unsigned int stat, const unsigned int type, const unsigned int value)
{
    if ((stat < NUM_STATS) && (type < NUM_STAT_VALUES))
    {
        if (type != STAT_ACTUAL)
        {
            m_statMatrix[stat][type] = value;
            m_statMatrix[stat][STAT_ACTUAL] = m_statMatrix[stat][STAT_CURRENT] + m_statMatrix[stat][STAT_MODIFIER];
        }
    }
    else
    {
        throw IndexOutOfRange(__FILE__, __LINE__, "statMatrix");
    }
}

