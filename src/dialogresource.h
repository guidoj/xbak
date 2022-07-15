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

#ifndef DIALOG_RESOURCE_H
#define DIALOG_RESOURCE_H

#include <map>
#include <vector>

#include "resourcedata.h"

class DialogData
{
public:
    unsigned int m_childDialogs;
    std::vector<std::string> m_text;
    std::vector<DialogData*> m_childData;
    DialogData();
    virtual ~DialogData();
};

class DialogResource
    : public ResourceData
{
private:
    std::map<const unsigned int, DialogData*> m_dialogMap;
    void readDialogData ( FileBuffer *buffer, DialogData *data );
public:
    DialogResource();
    virtual ~DialogResource();
    unsigned int getSize() const;
    bool find ( const unsigned int n, DialogData* &data );
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif
