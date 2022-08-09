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

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "configdata.h"
#include "gamedata.h"
#include "resourcearchive.h"
#include "resourcedata.h"
#include "resourceindex.h"

class FileManager
{
private:
    ResourceIndex m_resIndex;
    ResourceArchive m_resArchive;
    FileBuffer* loadConfig ( const std::string &name );
    void saveConfig ( const std::string &name, FileBuffer* buffer );
    void saveConfig ( const std::string &name, FileBuffer* buffer, const unsigned int n );
    FileBuffer* loadGame ( const std::string &name );
    void saveGame ( const std::string &name, FileBuffer* buffer );
    void saveGame ( const std::string &name, FileBuffer* buffer, const unsigned int n );
    FileBuffer* loadResource ( const std::string &name );
    void saveResource ( const std::string &name, FileBuffer* buffer );
    void saveResource ( const std::string &name, FileBuffer* buffer, const unsigned int n );
    static FileManager *m_instance;

protected:
    FileManager();

public:
    virtual ~FileManager();
    static FileManager* getInstance();
    static void cleanUp();
    bool configExists ( const std::string &name );
    void load ( ConfigData *cfg, const std::string &name );
    void save ( ConfigData *cfg, const std::string &name );
    bool gameExists ( const std::string &name );
    void load ( GameData *gam, const std::string &name );
    void save ( GameData *gam, const std::string &name );
    bool resourceExists ( const std::string &name );
    void load ( ResourceData *res, const std::string &name );
    void save ( ResourceData *res, const std::string &name );
    void extractResource ( const std::string &name );
    void extractAllResources();
    void archiveAllResources();
};

#endif

