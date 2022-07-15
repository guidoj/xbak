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

#ifndef RESOURCE_INDEX_H
#define RESOURCE_INDEX_H

#include <map>

#include "filebuffer.h"

struct ResourceIndexData
{
    unsigned int hashkey;
    std::streamoff offset;
    unsigned int size;
};

class ResourceIndex
{
private:
    std::string m_resourceFilename;
    unsigned int m_numResources;
    std::map <const std::string, ResourceIndexData> m_resIdxMap;
    std::map<const std::string, ResourceIndexData>::iterator m_resIdxIterator;
public:
    ResourceIndex();
    virtual ~ResourceIndex();
    void load ( const std::string &filename );
    void save ( const std::string &filename );
    std::string getResourceFilename() const;
    unsigned int getNumResources() const;
    bool find ( const std::string &name, ResourceIndexData &data );
    bool getFirst ( std::string& name, ResourceIndexData &data );
    bool getNext ( std::string& name, ResourceIndexData &data );
};

#endif

