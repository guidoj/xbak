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

#ifndef BOOK_RESOURCE_H
#define BOOK_RESOURCE_H

#include <vector>

#include "resourcedata.h"

const unsigned DECO_HORIZONTAL_FLIP = 0x01;
const unsigned DECO_VERTICAL_FLIP   = 0x02;

struct ImageInfo
{
    int xpos;
    int ypos;
    unsigned int id;
    unsigned int flag;
};

struct TextInfo
{
    bool paragraph;
    bool italic;
    std::string txt;
};

class PageData
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    unsigned int number;
    unsigned int id;
    unsigned int prevId;
    unsigned int nextId;
    unsigned int flag;
    bool showNumber;
    std::vector<ImageInfo> decorations;
    std::vector<ImageInfo> firstLetters;
    std::vector<TextInfo> textBlocks;
};

class BookResource: public ResourceData
{
private:
    std::vector<PageData> m_pages;
public:
    BookResource();
    virtual ~BookResource();
    unsigned int getSize() const;
    const PageData& getPage ( const unsigned int i ) const;
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif
