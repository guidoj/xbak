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

#ifndef MOVIE_RESOURCE_H
#define MOVIE_RESOURCE_H

#include <vector>

#include "taggedresource.h"

struct MovieChunk
{
    unsigned int code;
    std::string name;
    std::vector<int> data;
};

class MovieResource
    : public TaggedResource
{
private:
    std::string m_version;
    unsigned int m_pages;
    std::vector<MovieChunk *> m_movieChunks;
public:
    MovieResource();
    virtual ~MovieResource();
    std::string& getVersion();
    unsigned int getPages() const;
    std::vector<MovieChunk *> & getMovieChunks();
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif

