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

#ifndef GENERIC_FILE_H
#define GENERIC_FILE_H

#include "filebuffer.h"

class BasicFile
{
private:
    std::ifstream m_ifs;
    std::ofstream m_ofs;
public:
    BasicFile();
    virtual ~BasicFile();
    virtual std::string getDefaultPath() const;
    virtual std::string getAlternatePath() const;
    virtual std::string getLastResortPath() const;
    virtual std::string getStoragePath() const;
    void open ( const std::string &name, const bool writable );
    void close();
    void seek ( const std::streamoff offset );
    void seekEnd ( const std::streamoff offset );
    std::streamsize size();
    void load ( FileBuffer &buffer );
    void save ( FileBuffer &buffer );
    void save ( FileBuffer &buffer, const unsigned int n );
};

#endif
