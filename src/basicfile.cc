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

#include "basicfile.h"
#include "directories.h"
#include "exception.h"

BasicFile::BasicFile()
    : m_ifs()
    , m_ofs()
{}

BasicFile::~BasicFile()
{}

std::string
BasicFile::getDefaultPath() const
{
    return std::string("");
}

std::string
BasicFile::getAlternatePath() const
{
    return std::string("");
}

std::string
BasicFile::getLastResortPath() const
{
    return std::string("");
}

std::string
BasicFile::getStoragePath() const
{
    return std::string("");
}

void
BasicFile::open(const std::string &name, const bool writable)
{
    if (writable)
    {
        std::string filename = getStoragePath() + name;
        m_ofs.open(filename.c_str(), std::ios::out | std::ios::binary);
        if (m_ofs.fail())
        {
            throw OpenError(__FILE__, __LINE__, "(" + filename + ")");
        }
    }
    else
    {
        std::string filename = getDefaultPath() + name;
        m_ifs.open(filename.c_str(), std::ios::in | std::ios::binary);
        if (m_ifs.fail())
        {
            m_ifs.clear();
            filename = getAlternatePath() + name;
            m_ifs.open(filename.c_str(), std::ios::in | std::ios::binary);
            if (m_ifs.fail())
            {
                m_ifs.clear();
                filename = getLastResortPath() + name;
                m_ifs.open(filename.c_str(), std::ios::in | std::ios::binary);
                if (m_ifs.fail())
                {
                    throw OpenError(__FILE__, __LINE__, "(" + filename + ")");
                }
            }
        }
    }
}

void
BasicFile::close()
{
    if (m_ifs.is_open())
    {
        m_ifs.close();
    }
    if (m_ofs.is_open())
    {
        m_ofs.close();
    }
}

void
BasicFile::seek(const std::streamoff offset)
{
    if (m_ifs.is_open())
    {
        m_ifs.seekg(offset, std::ios::beg);
        if (m_ifs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
    }
    if (m_ofs.is_open())
    {
        m_ofs.seekp(offset, std::ios::beg);
        if (m_ofs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
    }
}

void
BasicFile::seekEnd(const std::streamoff offset)
{
    if (m_ifs.is_open())
    {
        m_ifs.seekg(offset, std::ios::end);
        if (m_ifs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
    }
    if (m_ofs.is_open())
    {
        m_ofs.seekp(offset, std::ios::end);
        if (m_ofs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
    }
}

std::streamsize
BasicFile::size()
{
    if (m_ifs.is_open())
    {
        m_ifs.seekg(0, std::ios::end);
        if (m_ifs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
        return m_ifs.tellg();
    }
    if (m_ofs.is_open())
    {
        m_ofs.seekp(0, std::ios::end);
        if (m_ofs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
        return m_ofs.tellp();
    }
    return 0;
}

void
BasicFile::load(FileBuffer &buffer)
{
    try
    {
        buffer.load(m_ifs);
    }
    catch (Exception &e)
    {
        e.print("BasicFile::Load");
        throw;
    }
}

void
BasicFile::save(FileBuffer &buffer)
{
    try
    {
        buffer.save(m_ofs);
    }
    catch (Exception &e)
    {
        e.print("BasicFile::Save");
        throw;
    }
}

void
BasicFile::save(FileBuffer &buffer, const unsigned int n)
{
    try
    {
        buffer.save(m_ofs, n);
    }
    catch (Exception &e)
    {
        e.print("BasicFile::Save");
        throw;
    }
}
