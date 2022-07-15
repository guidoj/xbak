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

#include "exception.h"
#include "resourcearchive.h"
#include "resourceindex.h"

ResourceIndex::ResourceIndex()
    : m_resourceFilename("")
    , m_numResources(0)
    , m_resIdxMap()
    , m_resIdxIterator(m_resIdxMap.begin())
{
}

ResourceIndex::~ResourceIndex()
{
    m_resIdxMap.clear();
}

void ResourceIndex::load(const std::string &filename)
{
    try
    {
        ResourceFile rmf;
        rmf.open(filename, false);
        FileBuffer rmfBuffer(rmf.size());
        rmf.seek(0);
        rmf.load(rmfBuffer);
        rmf.close();
        if ((rmfBuffer.getUint32LE() != 1) || (rmfBuffer.getUint16LE() != 4))
        {
            throw DataCorruption(__FILE__, __LINE__);
        }
        m_resourceFilename = rmfBuffer.getString(RES_FILENAME_LEN);
        m_numResources = rmfBuffer.getUint16LE();

        ResourceFile res;
        res.open(m_resourceFilename, false);
        FileBuffer resBuffer(RES_FILENAME_LEN + 4);
        for (unsigned int i = 0; i < m_numResources; i++)
        {
            unsigned int hashkey = rmfBuffer.getUint32LE();
            std::streamoff offset = rmfBuffer.getUint32LE();
            res.seek(offset);
            res.load(resBuffer);
            std::string resIdxName = resBuffer.getString(RES_FILENAME_LEN);
            ResourceIndexData resIdxData;
            resIdxData.hashkey = hashkey;
            resIdxData.offset = offset + RES_FILENAME_LEN + 4;
            resIdxData.size = resBuffer.getUint32LE();
            m_resIdxMap.insert(std::pair<const std::string, ResourceIndexData>(resIdxName, resIdxData));
        }
        res.close();
    }
    catch (Exception &e)
    {
        e.print("ResourceIndex::Load");
        throw;
    }
}

void ResourceIndex::save(const std::string &filename)
{
    try
    {
        FileBuffer rmfBuffer(4 + 2 + RES_FILENAME_LEN + 2 + m_numResources * (4 + 4));
        rmfBuffer.putUint32LE(1);
        rmfBuffer.putUint16LE(4);
        rmfBuffer.putString(m_resourceFilename, RES_FILENAME_LEN);
        rmfBuffer.putUint16LE(m_numResources);

        ResourceFile res;
        res.open(m_resourceFilename, false);
        FileBuffer resBuffer(RES_FILENAME_LEN + 4);
        unsigned int offset = 0;
        for (unsigned int i = 0; i < m_numResources; i++)
        {
            res.seek(offset);
            res.load(resBuffer);
            std::string resIdxName = resBuffer.getString(RES_FILENAME_LEN);
            ResourceIndexData resIdxData;
            find(resIdxName, resIdxData);
            rmfBuffer.putUint32LE(resIdxData.hashkey);
            rmfBuffer.putUint32LE(offset);
            offset += RES_FILENAME_LEN + 4 + resIdxData.size;
        }
        res.close();

        ResourceFile rmf;
        rmf.open(filename, true);
        rmf.save(rmfBuffer);
        rmf.close();
    }
    catch (Exception &e)
    {
        e.print("ResourceIndex::Save");
        throw;
    }
}

std::string ResourceIndex::getResourceFilename() const
{
    return m_resourceFilename;
}

unsigned int ResourceIndex::getNumResources() const
{
    return m_numResources;
}

bool ResourceIndex::find(const std::string &name, ResourceIndexData &data)
{
    std::map<const std::string, ResourceIndexData>::iterator it = m_resIdxMap.find(name);
    if (it != m_resIdxMap.end())
    {
        data = it->second;
        return true;
    }
    return false;
}

bool ResourceIndex::getFirst(std::string& name, ResourceIndexData &data)
{
    m_resIdxIterator = m_resIdxMap.begin();
    if (m_resIdxIterator != m_resIdxMap.end())
    {
        name = m_resIdxIterator->first;
        data = m_resIdxIterator->second;
        return true;
    }
    return false;
}


bool ResourceIndex::getNext(std::string& name, ResourceIndexData &data)
{
    if (m_resIdxIterator == m_resIdxMap.end())
    {
        return false;
    }
    m_resIdxIterator++;
    if (m_resIdxIterator != m_resIdxMap.end())
    {
        name = m_resIdxIterator->first;
        data = m_resIdxIterator->second;
        return true;
    }
    return false;
}
