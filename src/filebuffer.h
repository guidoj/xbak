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

#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <fstream>
#include <string>
#include <stdint.h>

const unsigned int COMPRESSION_LZW  = 0;
const unsigned int COMPRESSION_LZSS = 1;
const unsigned int COMPRESSION_RLE  = 2;

class FileBuffer
{
private:
    uint8_t * m_buffer;
    uint8_t * m_current;
    unsigned int m_size;
    unsigned int m_nextbit;
public:
    FileBuffer ( const unsigned int n );
    virtual ~FileBuffer();

    void load ( std::ifstream &ifs );
    void save ( std::ofstream &ofs );
    void save ( std::ofstream &ofs, const unsigned int n );
    void dump ( const unsigned int n = 0 );
    void copyFrom ( FileBuffer *buf, const unsigned int n );
    void copyTo ( FileBuffer *buf, const unsigned int n );
    void fill ( FileBuffer *buf );
    void rewind();
    void seek ( const unsigned int n );
    void skip ( const int n );

    void skipBits();
    unsigned int compressLZW ( FileBuffer *result );
    unsigned int compressLZSS ( FileBuffer *result );
    unsigned int compressRLE ( FileBuffer *result );
    unsigned int compress ( FileBuffer *result, const unsigned int method );
    unsigned int decompressLZW ( FileBuffer *result );
    unsigned int decompressLZSS ( FileBuffer *result );
    unsigned int decompressRLE ( FileBuffer *result );
    unsigned int decompress ( FileBuffer *result, const unsigned int method );

    bool atEnd() const;
    unsigned int getSize() const;
    unsigned int getBytesDone() const;
    unsigned int getBytesLeft() const;
    uint8_t * getCurrent() const;
    unsigned int getNextBit() const;

    uint8_t getUint8();
    uint16_t getUint16LE();
    uint16_t getUint16BE();
    uint32_t getUint32LE();
    uint32_t getUint32BE();
    int8_t getSint8();
    int16_t getSint16LE();
    int16_t getSint16BE();
    int32_t getSint32LE();
    int32_t getSint32BE();
    std::string getString();
    std::string getString ( const unsigned int len );
    void getData ( void * data, const unsigned int n );
    unsigned int getBits ( const unsigned int n );

    void putUint8 ( const uint8_t x );
    void putUint16LE ( const uint16_t x );
    void putUint16BE ( const uint16_t x );
    void putUint32LE ( const uint32_t x );
    void putUint32BE ( const uint32_t x );
    void putSint8 ( const int8_t x );
    void putSint16LE ( const int16_t x );
    void putSint16BE ( const int16_t x );
    void putSint32LE ( const int32_t x );
    void putSint32BE ( const int32_t x );
    void putString ( const std::string s );
    void putString ( const std::string s, const unsigned int len );
    void putData ( void * data, const unsigned int n );
    void putData ( const uint8_t x, const unsigned int n );
    void putBits ( const unsigned int x, const unsigned int n );
};

#endif

