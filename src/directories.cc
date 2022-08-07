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

#include <cstdlib>
#include <fstream>

#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "exception.h"
#include "directories.h"

Directories* Directories::m_instance = 0;

Directories::Directories()
    : m_resourcePath()
    , m_sharedPath()
    , m_userPath()
    , m_gamesPath()
    , m_capturePath()
    , m_dataPath()
    , m_timidityPath()
{
}

Directories::~Directories()
{}

Directories*
Directories::getInstance()
{
    if (!m_instance)
    {
        m_instance = new Directories();
    }
    return m_instance;
}

void
Directories::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

void
Directories::initialize()
{
    if (m_resourcePath.empty())
    {
        m_resourcePath = searchResources();
    }
    m_sharedPath = "";
#if defined(WIN32) || defined(__MACOS__) || defined(__MACOSX__) || defined(__APPLE__) || defined(__APPLE_CC__)
    m_userPath = "";
    m_gamesPath = "";
    m_capturePath = "";
    m_dataPath = "";
    m_timidityPath = "";
#else
    m_userPath = std::string(getenv("HOME")) + "/xbak/";
    m_gamesPath = m_userPath + "games/";
    m_capturePath = m_userPath + "capture/";
    m_dataPath = m_userPath + "data/";
    m_timidityPath = m_userPath + "timidity/";
#endif
    createPath(m_userPath);
    createPath(m_gamesPath);
    createPath(m_capturePath);
    createPath(m_dataPath);
    createPath(m_timidityPath);
}

void
Directories::createPath(const std::string &path)
{
#if defined(WIN32)
    // TODO
#elif defined(__MACOS__) || defined(__MACOSX__) || defined(__APPLE__) || defined(__APPLE_CC__)
    // TODO
#else
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) == -1)
    {
        if (errno == ENOENT)
        {
            if (mkdir(path.c_str(), S_IRWXU| S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1)
            {
                throw IOError(__FILE__, __LINE__);
            }
        }
        else
        {
            throw FileNotFound(__FILE__, __LINE__, path);
        }
    }
#endif
}

const std::string SEARCH_RESOURCE_FILE = "krondor.001";
const std::string SEARCH_RESOURCE_PATH[] =
{
    "./",
    "/krondor/",
    "./krondor/",
    "../krondor/",
    "/opt/krondor/",
    "/bakcd/",
    "./bakcd/",
    "../bakcd/",
    "/opt/bakcd/",
    ""
};

void
Directories::verifyPath(const std::string &path) const
{
    std::string filename = path + SEARCH_RESOURCE_FILE;
    try
    {
        std::ifstream ifs;
        ifs.open(filename.c_str(), std::ios::in | std::ios::binary);
        if (ifs.is_open())
        {
            ifs.close();
        }
    }
    catch (...)
    {
        throw FileNotFound(__FILE__, __LINE__, filename);
    }
}

std::string
Directories::searchResources() const
{
    unsigned int i = 0;
    while (SEARCH_RESOURCE_PATH[i] != "")
    {
        try
        {
            std::string path = SEARCH_RESOURCE_PATH[i];
            verifyPath(path);
            return path;
        }
        catch (...)
        {
            /* continu */
        }
        i++;
    }
    throw FileNotFound(__FILE__, __LINE__, SEARCH_RESOURCE_FILE);
    return "";
}

void
Directories::setResourcePath(const std::string &path)
{
    m_resourcePath = path;
}

std::string
Directories::getResourcePath() const
{
    return m_resourcePath;
}

std::string
Directories::getSharedPath() const
{
    return m_sharedPath;
}

std::string
Directories::getUserPath() const
{
    return m_userPath;
}

std::string
Directories::getGamesPath() const
{
    return m_gamesPath;
}

std::string
Directories::getCapturePath() const
{
    return m_capturePath;
}

std::string
Directories::getDataPath() const
{
    return m_dataPath;
}

std::string
Directories::getTimidityPath() const
{
    return m_timidityPath;
}
