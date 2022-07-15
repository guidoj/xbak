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

#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include <string>

class Directories
{
private:
    std::string m_resourcePath;
    std::string m_sharedPath;
    std::string m_userPath;
    std::string m_gamesPath;
    std::string m_capturePath;
    std::string m_dataPath;
    static Directories *m_instance;
    void createPath ( const std::string& path );
    void verifyPath ( const std::string& path ) const;
    std::string searchResources() const;
protected:
    Directories();
public:
    ~Directories();
    static Directories* getInstance();
    static void cleanUp();
    void initialize();
    std::string getResourcePath() const;
    std::string getSharedPath() const;
    std::string getUserPath() const;
    std::string getGamesPath() const;
    std::string getCapturePath() const;
    std::string getDataPath() const;
    void setResourcePath ( const std::string &path );
};

#endif
