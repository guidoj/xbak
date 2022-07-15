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

#include <algorithm>
#include <cctype>

#include "exception.h"
#include "resourcetag.h"
#include "movieresource.h"

MovieResource::MovieResource()
    : TaggedResource()
    , m_version("")
    , m_pages(0)
    , m_movieChunks()
{}

MovieResource::~MovieResource()
{
    clear();
}

std::string&
MovieResource::getVersion()
{
    return m_version;
}

unsigned int
MovieResource::getPages() const
{
    return m_pages;
}

std::vector<MovieChunk *> &
MovieResource::getMovieChunks()
{
    return m_movieChunks;
}

void
MovieResource::clear()
{
    for (unsigned int i = 0; i < m_movieChunks.size(); i++)
    {
        m_movieChunks[i]->data.clear();
        delete m_movieChunks[i];
    }
    m_movieChunks.clear();
}

void
MovieResource::load(FileBuffer *buffer)
{
    try
    {
        clear();
        split(buffer);
        FileBuffer *verbuf;
        FileBuffer *pagbuf;
        FileBuffer *tt3buf;
        FileBuffer *tagbuf;
        if (!find(TAG_VER, verbuf) ||
                !find(TAG_PAG, pagbuf) ||
                !find(TAG_TT3, tt3buf) ||
                !find(TAG_TAG, tagbuf))
        {
            clearTags();
            throw DataCorruption(__FILE__, __LINE__);
        }
        m_version = verbuf->getString();
        m_pages = pagbuf->getUint16LE();
        tt3buf->skip(1);
        FileBuffer *tmpbuf = new FileBuffer(tt3buf->getUint32LE());
        tt3buf->decompressRLE(tmpbuf);
        ResourceTag tags;
        tags.load(tagbuf);
        while (!tmpbuf->atEnd())
        {
            MovieChunk *mc = new MovieChunk;
            unsigned int code = tmpbuf->getUint16LE();
            unsigned int size = code & 0x000f;
            code &= 0xfff0;
            mc->code = code;
            if ((code == 0x1110) && (size == 1))
            {
                unsigned int id = tmpbuf->getUint16LE();
                mc->data.push_back(id);
                std::string name;
                if (tags.find(id, name))
                {
                    mc->name = name;
                }
            }
            else if (size == 15)
            {
                mc->name = tmpbuf->getString();
                transform(mc->name.begin(), mc->name.end(), mc->name.begin(), toupper);
                if (tmpbuf->getBytesLeft() & 1)
                {
                    tmpbuf->skip(1);
                }
            }
            else
            {
                for (unsigned int i = 0; i < size; i++)
                {
                    mc->data.push_back(tmpbuf->getSint16LE());
                }
            }
            m_movieChunks.push_back(mc);
        }
        delete tmpbuf;
        clearTags();
    }
    catch (Exception &e)
    {
        e.print("MovieResource::Load");
        clearTags();
        throw;
    }
}

unsigned int
MovieResource::save(FileBuffer *buffer)
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch (Exception &e)
    {
        e.print("MovieResource::Save");
        throw;
    }
}
