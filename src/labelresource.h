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

#ifndef LABEL_RESOURCE_H
#define LABEL_RESOURCE_H

#include <vector>

#include "resourcedata.h"

const int LBL_STANDARD = 0;
const int LBL_TITLE    = 3;

struct LabelData
{
    int xpos;
    int ypos;
    int type;
    int color;
    int shadow;
    std::string label;
};

class LabelResource
    : public ResourceData
{
private:
    std::vector<LabelData> m_data;
public:
    LabelResource();
    virtual ~LabelResource();
    unsigned int getSize() const;
    LabelData& getLabelData ( const unsigned int n );
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif

