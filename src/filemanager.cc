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

#include "configfile.h"
#include "exception.h"
#include "filemanager.h"
#include "gamefile.h"
#include "resourcefile.h"

FileManager* FileManager::m_instance = 0;

FileManager::FileManager()
{
    m_resIndex.load("krondor.rmf");
    m_resArchive.open(m_resIndex.getResourceFilename(), false);
}

FileManager::~FileManager()
{
    m_resArchive.close();
}

FileManager*
FileManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new FileManager();
    }
    return m_instance;
}

void
FileManager::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

FileBuffer*
FileManager::loadConfig(const std::string &name)
{
    try
    {
        ConfigFile cfgfile;
        cfgfile.open(name, false);
        FileBuffer *buffer = new FileBuffer(cfgfile.size());
        cfgfile.seek(0);
        cfgfile.load(*buffer);
        cfgfile.close();
        return buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::loadConfig");
        throw;
    }
    return 0;
}

void
FileManager::saveConfig(const std::string &name, FileBuffer* buffer)
{
    try
    {
        ConfigFile cfgfile;
        cfgfile.open(name, true);
        cfgfile.save(*buffer);
        cfgfile.close();
    }
    catch (Exception &e)
    {
        e.print("FileManager::saveConfig");
        throw;
    }
}

void
FileManager::saveConfig(const std::string &name, FileBuffer* buffer, const unsigned int n)
{
    try
    {
        ConfigFile cfgfile;
        cfgfile.open(name, true);
        cfgfile.save(*buffer, n);
        cfgfile.close();
    }
    catch (Exception &e)
    {
        e.print("FileManager::saveConfig");
        throw;
    }
}

FileBuffer*
FileManager::loadGame(const std::string &name)
{
    try
    {
        GameFile gamfile;
        gamfile.open(name, false);
        FileBuffer *buffer = new FileBuffer(gamfile.size());
        gamfile.seek(0);
        gamfile.load(*buffer);
        gamfile.close();
        return buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::loadGame");
        throw;
    }
    return 0;
}

void
FileManager::saveGame(const std::string &name, FileBuffer* buffer)
{
    try
    {
        GameFile gamfile;
        gamfile.open(name, true);
        gamfile.save(*buffer);
        gamfile.close();
    }
    catch (Exception &e)
    {
        e.print("FileManager::saveGame");
        throw;
    }
}

void
FileManager::saveGame(const std::string &name, FileBuffer* buffer, const unsigned int n)
{
    try
    {
        GameFile gamfile;
        gamfile.open(name, true);
        gamfile.save(*buffer, n);
        gamfile.close();
    }
    catch (Exception &e)
    {
        e.print("FileManager::saveGame");
        throw;
    }
}

FileBuffer*
FileManager::loadResource(const std::string &name)
{
    try
    {
        ResourceFile resfile;
        resfile.open(name, false);
        FileBuffer *buffer = new FileBuffer(resfile.size());
        resfile.seek(0);
        resfile.load(*buffer);
        resfile.close();
        return buffer;
    }
    catch (Exception &e1)
    {
        ResourceIndexData resIdxData = {0, 0, 0};
        if (m_resIndex.find(name, resIdxData) && (resIdxData.size != 0))
        {
            try
            {
                FileBuffer *buffer = new FileBuffer(resIdxData.size);
                m_resArchive.loadResource(*buffer, resIdxData.offset);
                return buffer;
            }
            catch (Exception &e2)
            {
                e2.print("FileManager::loadResource");
                throw;
            }
        }
        else
        {
            throw FileNotFound(__FILE__, __LINE__, name);
        }
    }
    return 0;
}

void
FileManager::saveResource(const std::string &name, FileBuffer* buffer)
{
    try
    {
        ResourceFile resfile;
        resfile.open(name, true);
        resfile.save(*buffer);
        resfile.close();
    }
    catch (Exception &e)
    {
        e.print("FileManager::saveResource");
        throw;
    }
}

void
FileManager::saveResource(const std::string &name, FileBuffer* buffer, const unsigned int n)
{
    try
    {
        ResourceFile resfile;
        resfile.open(name, true);
        resfile.save(*buffer, n);
        resfile.close();
    }
    catch (Exception &e)
    {
        e.print("FileManager::saveResource");
        throw;
    }
}

bool
FileManager::configExists(const std::string &name)
{
    try
    {
        ConfigFile cfgfile;
        cfgfile.open(name, false);
        cfgfile.close();
        return true;
    }
    catch (Exception &e)
    {
        return false;
    }
    return false;
}

void
FileManager::load(ConfigData *cfg, const std::string &name)
{
    try
    {
        FileBuffer *buffer;
        buffer = loadConfig(name);
        cfg->load(buffer);
        delete buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::load");
        throw;
    }
}

void
FileManager::save(ConfigData *cfg, const std::string &name)
{
    try
    {
        FileBuffer *buffer = new FileBuffer(16);
        unsigned int size = cfg->save(buffer);
        saveConfig(name, buffer, size);
        delete buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::Save");
        throw;
    }
}

bool
FileManager::gameExists(const std::string &name)
{
    try
    {
        GameFile gamfile;
        gamfile.open(name, false);
        gamfile.close();
        return true;
    }
    catch (Exception &e)
    {
        return false;
    }
    return false;
}

void
FileManager::load(GameData *gam, const std::string &name)
{
    try
    {
        FileBuffer *buffer;
        buffer = loadGame(name);
        gam->load(buffer);
        delete buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::Load");
        throw;
    }
}

void
FileManager::save(GameData *gam, const std::string &name)
{
    try
    {
        FileBuffer *buffer = new FileBuffer(400000);
        unsigned int size = gam->save(buffer);
        saveGame(name, buffer, size);
        delete buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::save");
        throw;
    }
}

bool
FileManager::resourceExists(const std::string &name)
{
    try
    {
        ResourceFile resfile;
        resfile.open(name, false);
        resfile.close();
        return true;
    }
    catch (Exception &e1)
    {
        ResourceIndexData resIdxData = {0, 0, 0};
        return (m_resIndex.find(name, resIdxData) && (resIdxData.size != 0));
    }
    return false;
}

void
FileManager::load(ResourceData *res, const std::string &name)
{
    try
    {
        FileBuffer *buffer;
        buffer = loadResource(name);
        res->load(buffer);
        delete buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::load");
        throw;
    }
}

void
FileManager::save(ResourceData *res, const std::string &name)
{
    try
    {
        FileBuffer *buffer = new FileBuffer(0x20000);
        unsigned int size = res->save(buffer);
        saveResource(name, buffer, size);
        delete buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::Save");
        throw;
    }
}

void
FileManager::extractResource(const std::string &name)
{
    try
    {
        FileBuffer *buffer;
        buffer = loadResource(name);
        saveResource(name, buffer);
        delete buffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::extractResource");
        throw;
    }
}

void
FileManager::extractAllResources()
{
    try
    {
        std::string resName;
        ResourceIndexData resIdxData = {0, 0, 0};
        if (m_resIndex.getFirst(resName, resIdxData))
        {
            do
            {
                FileBuffer *buffer = new FileBuffer(resIdxData.size);
                m_resArchive.loadResource(*buffer, resIdxData.offset);
                saveResource(resName, buffer);
                delete buffer;
            }
            while (m_resIndex.getNext(resName, resIdxData));
        }
    }
    catch (Exception &e)
    {
        e.print("FileManager::extractAllResources");
        throw;
    }
}

void
FileManager::archiveAllResources()
{
    try
    {
        std::string resName;
        ResourceIndexData resIdxData = {0, 0, 0};
        FileBuffer *archiveBuffer = new FileBuffer(0x1000000);
        if (m_resIndex.getFirst(resName, resIdxData))
        {
            do
            {
                FileBuffer *buffer = new FileBuffer(resIdxData.size);
                m_resArchive.loadResource(*buffer, resIdxData.offset);
                archiveBuffer->putString(resName, RES_FILENAME_LEN);
                archiveBuffer->putUint32LE(resIdxData.size);
                archiveBuffer->copyFrom(buffer, resIdxData.size);
                delete buffer;
            }
            while (m_resIndex.getNext(resName, resIdxData));
        }
        saveResource(m_resIndex.getResourceFilename(), archiveBuffer, archiveBuffer->getBytesDone());
        m_resIndex.save("krondor.rmf");
        delete archiveBuffer;
    }
    catch (Exception &e)
    {
        e.print("FileManager::archiveAllResources");
        throw;
    }
}
