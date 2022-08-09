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

#ifndef TAGGED_IMAGE_RESOURCE_H
#define TAGGED_IMAGE_RESOURCE_H

#include <vector>

#include "image.h"
#include "taggedresource.h"

class TaggedImageResource : public TaggedResource
{
private:
    unsigned int m_numImages;
    std::vector<Image *> m_images;
public:
    TaggedImageResource();
    virtual ~TaggedImageResource();
    unsigned int getNumImages() const;
    Image * getImage ( unsigned int n ) const;
    void clear();
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif
