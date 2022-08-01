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

#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>

#include <SDL_endian.h>

#include "defines.h"
#include "exception.h"
#include "filebuffer.h"

FileBuffer::FileBuffer(const unsigned long n)
{
    m_buffer = new uint8_t[n];
    memset(m_buffer, 0, n);
    m_current = m_buffer;
    m_size = n;
    m_nextbit = 0;
}

FileBuffer::~FileBuffer()
{
    if (m_buffer)
    {
        delete[] m_buffer;
    }
}

void
FileBuffer::copyFrom(FileBuffer *buf, const unsigned long n)
{
    if (m_buffer && n && (m_current + n <= m_buffer + m_size))
    {
        buf->getData(m_current, n);
        m_current += n;
    }
}

void
FileBuffer::copyTo(FileBuffer *buf, const unsigned long n)
{
    if (m_buffer && n && (m_current + n <= m_buffer + m_size))
    {
        buf->putData(m_current, n);
        m_current += n;
    }
}

void
FileBuffer::fill(FileBuffer *buf)
{
    if (m_buffer)
    {
        m_current = m_buffer;
        buf->getData(m_buffer, MIN(m_size, buf->getSize()));
    }
}

void
FileBuffer::load(std::ifstream &ifs)
{
    if (ifs.is_open())
    {
        m_current = m_buffer;
        ifs.read((char *)m_buffer, m_size);
        if (ifs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
    }
    else
    {
        throw OpenError(__FILE__, __LINE__);
    }
}

void
FileBuffer::save(std::ofstream &ofs)
{
    if (ofs.is_open())
    {
        m_current = m_buffer;
        ofs.write((char *)m_buffer, m_size);
        if (ofs.fail())
        {
            throw IOError(__FILE__, __LINE__);
        }
    }
    else
    {
        throw OpenError(__FILE__, __LINE__);
    }
}

void
FileBuffer::save(std::ofstream &ofs, const unsigned long n)
{
    if (ofs.is_open())
    {
        if (n <= m_size)
        {
            m_current = m_buffer;
            ofs.write((char *)m_buffer, n);
            if (ofs.fail())
            {
                throw IOError(__FILE__, __LINE__);
            }
        }
        else
        {
            throw BufferEmpty(__FILE__, __LINE__);
        }
    }
    else
    {
        throw OpenError(__FILE__, __LINE__);
    }
}

void
FileBuffer::dump(const unsigned long n)
{
    uint8_t* tmp = m_current;
    unsigned int count = 0;
    std::cout << std::setbase(16) << std::setfill('0') << std::setw(8) << count << ": ";
    while ((tmp < (m_buffer + m_size)) && ((tmp < (m_current + n)) || (n == 0)))
    {
        std::cout << std::setw(2) << (unsigned int)*tmp++ << " ";
        if ((++count & 0x1f) == 0)
        {
            std::cout << std::endl << std::setw(8) << count << ": ";
        }
        else if ((count & 0x07) == 0)
        {
            std::cout << "| ";
        }
    }
    std::cout << std::setbase(10) << std::setfill(' ') << std::endl;
}

void
FileBuffer::seek(const unsigned long n)
{
    if ((m_current) && (n <= m_size))
    {
        m_current = m_buffer + n;
    }
}

void
FileBuffer::skip(const long n)
{
    if ((m_current) && (m_current + n <= m_buffer + m_size))
    {
        m_current += n;
    }
}

void
FileBuffer::skipBits()
{
    if (m_nextbit)
    {
        skip(1);
        m_nextbit = 0;
    }
}

typedef union _HashTableEntry
{
    uint32_t code;
    struct
    {
        uint16_t prefix;
        uint8_t  append;
    }
    entry;
} HashTableEntry;

unsigned long
FileBuffer::compressLZW(FileBuffer *result)
{
    try
    {
        std::map<uint32_t, uint16_t> hashtable;
        unsigned int n_bits = 9;
        unsigned int free_entry = 257;
        unsigned int bitpos = 0;
        bool entry_written = false;
        HashTableEntry hte;
        hte.entry.prefix = getUint8();
        while (!atEnd() && !result->atEnd())
        {
            hte.entry.append = getUint8();
            std::map<uint32_t, uint16_t>::iterator it = hashtable.find(hte.code);
            if (it == hashtable.end())
            {
                result->putBits(hte.entry.prefix, n_bits);
                bitpos += n_bits;
                entry_written = true;
                hashtable.insert(std::pair<uint32_t, uint16_t>(hte.code, free_entry));
                hte.entry.prefix = hte.entry.append;
                free_entry++;
                if (free_entry >= (unsigned int)(1 << n_bits))
                {
                    if (n_bits < 12)
                    {
                        n_bits++;
                    }
                    else
                    {
                        hashtable.clear();
                        free_entry = 256;
                        result->putBits(free_entry, n_bits);
                        result->skipBits();
                        result->skip((((bitpos-1)+((n_bits<<3)-(bitpos-1+(n_bits<<3))%(n_bits<<3)))-bitpos)>>3);
                        n_bits = 9;
                        bitpos = 0;
                    }
                }
            }
            else
            {
                hte.entry.prefix = it->second;
                entry_written = false;
            }
        }
        if (!entry_written)
        {
            result->putBits(hte.entry.prefix, n_bits);
        }
        result->skipBits();
        hashtable.clear();
        unsigned long res = result->getBytesDone();
        result->rewind();
        return res;
    }
    catch (Exception &e)
    {
        e.print("FileBuffer::CompressLZW");
        throw;
    }
    return 0;
}

unsigned long
FileBuffer::compressLZSS(FileBuffer *result)
{
    try
    {
        uint8_t *data = getCurrent();
        uint8_t *curr = getCurrent();
        uint8_t *codeptr = result->getCurrent();
        uint8_t byte = getUint8();
        uint8_t code = 0;
        uint8_t mask = 0;
        while (!atEnd() && !result->atEnd())
        {
            if (!mask)
            {
                *codeptr = code;
                codeptr = result->getCurrent();
                result->skip(1);
                code = 0;
                mask = 0x01;
            }
            unsigned int off = 0;
            unsigned int len = 0;
            uint8_t *ptr = curr;
            while (ptr > data)
            {
                ptr--;
                if (*ptr == byte)
                {
                    off = ptr - data;
                    len = 1;
                    while ((curr + len < m_buffer + m_size) && (ptr[len] == curr[len]))
                    {
                        len++;
                    }
                }
            }
            if (len < 5)
            {
                code |= mask;
                result->putUint8(byte);
            }
            else
            {
                result->putUint16LE(off);
                result->putUint8(len - 5);
                skip(len - 1);
            }
            curr = getCurrent();
            if (!atEnd())
            {
                byte = getUint8();
            }
            mask <<= 1;
        }
        *codeptr = code;
        unsigned long res = result->getBytesDone();
        result->rewind();
        return res;
    }
    catch (Exception &e)
    {
        e.print("FileBuffer::CompressLZSS");
        throw;
    }
    return 0;
}

unsigned long
FileBuffer::compressRLE(FileBuffer *result)
{
    try
    {
        uint8_t *skipptr = getCurrent();
        uint8_t byte = 0;
        uint8_t next = getUint8();
        unsigned int count;
        unsigned int skipped = 0;
        while (!atEnd() && !result->atEnd())
        {
            count = 1;
            do
            {
                byte = next;
                next = getUint8();
                count++;
            }
            while (!atEnd() && (next == byte));
            if (next != byte)
            {
                count--;
            }
            if (count > 3)
            {
                if (skipped > 0)
                {
                    while (skipped > 0)
                    {
                        unsigned int n;
                        if (skipped > 127)
                        {
                            n = 127;
                        }
                        else
                        {
                            n = skipped & 0x7f;
                        }
                        result->putUint8(n);
                        result->putData(skipptr, n);
                        skipped -= n;
                        skipptr += n;
                    }
                }
                while (count > 3)
                {
                    unsigned int n;
                    if (count > 127)
                    {
                        n = 127;
                    }
                    else
                    {
                        n = count & 0x7f;
                    }
                    result->putUint8(n | 0x80);
                    result->putUint8(byte);
                    count -= n;
                }
                skipped = count;
                skipptr = getCurrent() - skipped - 1;
            }
            else
            {
                skipped += count;
            }
        }
        if (next != byte)
        {
            skipped++;
        }
        if (skipped > 0)
        {
            skip(-skipped);
            while (skipped > 0)
            {
                unsigned int n = skipped & 0x7f;
                result->putUint8(n);
                result->copyFrom(this, n);
                skipped -= n;
            }
        }
        unsigned long res = result->getBytesDone();
        result->rewind();
        return res;
    }
    catch (Exception &e)
    {
        e.print("FileBuffer::CompressRLE");
        throw;
    }
    return 0;
}

unsigned long
FileBuffer::compress(FileBuffer *result, const unsigned int method)
{
    switch (method)
    {
    case COMPRESSION_LZW:
        return compressLZW(result);
        break;
    case COMPRESSION_LZSS:
        return compressLZSS(result);
        break;
    case COMPRESSION_RLE:
        return compressRLE(result);
        break;
    default:
        throw CompressionError(__FILE__, __LINE__);
        break;
    }
}

typedef struct _CodeTableEntry
{
    uint16_t prefix;
    uint8_t  append;
}
CodeTableEntry;

unsigned long
FileBuffer::decompressLZW(FileBuffer *result)
{
    try
    {
        CodeTableEntry *codetable = new CodeTableEntry[4096];
        uint8_t *decodestack = new uint8_t[4096];
        uint8_t *stackptr = decodestack;
        unsigned int n_bits = 9;
        unsigned int free_entry = 257;
        unsigned int oldcode = getBits(n_bits);
        unsigned int lastbyte = oldcode;
        unsigned int bitpos = 0;
        result->putUint8(oldcode);
        while ((getBitsLeft() >= n_bits) && !result->atEnd())
        {
            unsigned int newcode = getBits(n_bits);
            bitpos += n_bits;
            if (newcode == 256)
            {
                skipBits();
                skip((((bitpos-1)+((n_bits<<3)-(bitpos-1+(n_bits<<3))%(n_bits<<3)))-bitpos)>>3);
                n_bits = 9;
                free_entry = 256;
                bitpos = 0;
            }
            else
            {
                unsigned int code = newcode;
                if (code >= free_entry)
                {
                    *stackptr++ = lastbyte;
                    code = oldcode;
                }
                while (code >= 256)
                {
                    *stackptr++ = codetable[code].append;
                    code = codetable[code].prefix;
                }
                *stackptr++ = code;
                lastbyte = code;
                while (stackptr > decodestack)
                {
                    result->putUint8(*--stackptr);
                }
                if (free_entry < 4096)
                {
                    codetable[free_entry].prefix = oldcode;
                    codetable[free_entry].append = lastbyte;
                    free_entry++;
                    if ((free_entry >= (unsigned int)(1 << n_bits)) && (n_bits < 12))
                    {
                        n_bits++;
                        bitpos = 0;
                    }
                }
                oldcode = newcode;
            }
        }
        delete[] decodestack;
        delete[] codetable;
        unsigned long res = result->getBytesDone();
        result->rewind();
        return res;
    }
    catch (Exception &e)
    {
        e.print("FileBuffer::DecompressLZW");
        throw;
    }
    return 0;
}

unsigned long
FileBuffer::decompressLZSS(FileBuffer *result)
{
    try
    {
        uint8_t *data = result->getCurrent();
        uint8_t code = 0;
        uint8_t mask = 0;
        while (!atEnd() && !result->atEnd())
        {
            if (!mask)
            {
                code = getUint8();
                mask = 0x01;
            }
            if (code & mask)
            {
                result->putUint8(getUint8());
            }
            else
            {
                unsigned int off = getUint16LE();
                unsigned int len = getUint8() + 5;
                result->putData(data + off, len);
            }
            mask <<= 1;
        }
        unsigned long res = result->getBytesDone();
        result->rewind();
        return res;
    }
    catch (Exception &e)
    {
        e.print("FileBuffer::DecompressLZSS");
        throw;
    }
    return 0;
}

unsigned long
FileBuffer::decompressRLE(FileBuffer *result)
{
    try
    {
        while (!atEnd() && !result->atEnd())
        {
            uint8_t control = getUint8();
            if (control & 0x80)
            {
                result->putData(getUint8(), control & 0x7f);
            }
            else
            {
                result->copyFrom(this, control);
            }
        }
        unsigned long res = result->getBytesDone();
        result->rewind();
        return res;
    }
    catch (Exception &e)
    {
        e.print("FileBuffer::DecompressRLE");
        throw;
    }
    return 0;
}

unsigned long
FileBuffer::decompress(FileBuffer *result, const unsigned int method)
{
    switch (method)
    {
    case COMPRESSION_LZW:
        if ((getUint8() != 0x02) || (getUint32LE() != result->getSize()))
        {
            throw DataCorruption(__FILE__, __LINE__);
        }
        return decompressLZW(result);
        break;
    case COMPRESSION_LZSS:
        return decompressLZSS(result);
        break;
    case COMPRESSION_RLE:
        return decompressRLE(result);
        break;
    default:
        throw CompressionError(__FILE__, __LINE__);
        break;
    }
}

bool
FileBuffer::atEnd() const
{
    return (m_current >= m_buffer + m_size);
}

unsigned long
FileBuffer::getSize() const
{
    return m_size;
}

unsigned long
FileBuffer::getBytesDone() const
{
    return (m_current - m_buffer);
}

unsigned long
FileBuffer::getBytesLeft() const
{
    return (m_buffer + m_size - m_current);
}

unsigned long
FileBuffer::getBitsLeft() const
{
    return (((m_buffer + m_size - m_current) << 3) - m_nextbit);
}

uint8_t *
FileBuffer::getCurrent() const
{
    return m_current;
}

unsigned int
FileBuffer::getNextBit() const
{
    return m_nextbit;
}

void
FileBuffer::rewind()
{
    m_current = m_buffer;
}

uint8_t
FileBuffer::getUint8()
{
    uint8_t n;
    getData(&n, 1);
    return n;
}

uint16_t
FileBuffer::getUint16LE()
{
    uint16_t n;
    getData(&n, 2);
    return SDL_SwapLE16(n);
}

uint16_t
FileBuffer::getUint16BE()
{
    uint16_t n;
    getData(&n, 2);
    return SDL_SwapBE16(n);
}

uint32_t
FileBuffer::getUint32LE()
{
    uint32_t n;
    getData(&n, 4);
    return SDL_SwapLE32(n);
}

uint32_t
FileBuffer::getUint32BE()
{
    uint32_t n;
    getData(&n, 4);
    return SDL_SwapBE32(n);
}

int8_t
FileBuffer::getSint8()
{
    int8_t n;
    getData(&n, 1);
    return n;
}

int16_t
FileBuffer::getSint16LE()
{
    int16_t n;
    getData(&n, 2);
    return SDL_SwapLE16(n);
}

int16_t
FileBuffer::getSint16BE()
{
    int16_t n;
    getData(&n, 2);
    return SDL_SwapBE16(n);
}

int32_t
FileBuffer::getSint32LE()
{
    int32_t n;
    getData(&n, 4);
    return SDL_SwapLE32(n);
}

int32_t
FileBuffer::getSint32BE()
{
    int32_t n;
    getData(&n, 4);
    return SDL_SwapBE32(n);
}

std::string
FileBuffer::getString()
{
    if (m_current)
    {
        std::string s((char *)m_current);
        if ((m_current + s.length() + 1) <= (m_buffer + m_size))
        {
            m_current += s.length() + 1;
            return s;
        }
        else
        {
            throw BufferEmpty(__FILE__, __LINE__);
        }
    }
    return "";
}

std::string
FileBuffer::getString(const unsigned int len)
{
    if ((m_current) && (m_current + len <= m_buffer + m_size))
    {
        std::string s((char *)m_current);
        m_current += len;
        return s;
    }
    else
    {
        throw BufferEmpty(__FILE__, __LINE__);
    }
    return "";
}

void
FileBuffer::getData(void *data,
                    const unsigned int n)
{
    if (m_current + n <= m_buffer + m_size)
    {
        memcpy(data, m_current, n);
        m_current += n;
    }
    else
    {
        throw BufferEmpty(__FILE__, __LINE__);
    }
}

unsigned int
FileBuffer::getBits(const unsigned int n)
{
    if (m_current + ((m_nextbit + n + 7)/8) <= m_buffer + m_size)
    {
        unsigned int x = 0;
        for (unsigned int i = 0; i < n; i++)
        {
            if (*m_current & (1 << m_nextbit))
            {
                x += (1 << i);
            }
            m_nextbit++;
            if (m_nextbit > 7)
            {
                m_current++;
                m_nextbit = 0;
            }
        }
        return x;
    }
    else
    {
        throw BufferEmpty(__FILE__, __LINE__);
    }
}

void
FileBuffer::putUint8(const uint8_t x)
{
    uint8_t xx = x;
    putData(&xx, 1);
}

void
FileBuffer::putUint16LE(const uint16_t x)
{
    uint16_t xx = SDL_SwapLE16(x);
    putData(&xx, 2);
}

void
FileBuffer::putUint16BE(const uint16_t x)
{
    uint16_t xx = SDL_SwapBE16(x);
    putData(&xx, 2);
}

void
FileBuffer::putUint32LE(const uint32_t x)
{
    uint32_t xx = SDL_SwapLE32(x);
    putData(&xx, 4);
}

void
FileBuffer::putUint32BE(const uint32_t x)
{
    uint32_t xx = SDL_SwapBE32(x);
    putData(&xx, 4);
}

void
FileBuffer::putSint8(const int8_t x)
{
    int8_t xx = x;
    putData(&xx, 1);
}

void
FileBuffer::putSint16LE(const int16_t x)
{
    int16_t xx = SDL_SwapLE16(x);
    putData(&xx, 2);
}

void
FileBuffer::putSint16BE(const int16_t x)
{
    int16_t xx = SDL_SwapBE16(x);
    putData(&xx, 2);
}

void
FileBuffer::putSint32LE(const int32_t x)
{
    int32_t xx = SDL_SwapLE32(x);
    putData(&xx, 4);
}

void
FileBuffer::putSint32BE(const int32_t x)
{
    int32_t xx = SDL_SwapBE32(x);
    putData(&xx, 4);
}

void
FileBuffer::putString(const std::string s)
{
    if ((m_current) && (m_current + s.length() + 1 <= m_buffer + m_size))
    {
        strncpy((char *)m_current, s.c_str(), s.length() + 1);
        m_current += s.length() + 1;
    }
    else
    {
        throw BufferFull(__FILE__, __LINE__);
    }
}

void
FileBuffer::putString(const std::string s, const unsigned int len)
{
    if ((m_current) && (m_current + len <= m_buffer + m_size))
    {
        memset(m_current, 0, len);
        strncpy((char *)m_current, s.c_str(), len);
        m_current += len;
    }
    else
    {
        throw BufferFull(__FILE__, __LINE__);
    }
}

void
FileBuffer::putData(void *data, const unsigned int n)
{
    if (m_current + n <= m_buffer + m_size)
    {
        memcpy(m_current, data, n);
        m_current += n;
    }
    else
    {
        throw BufferFull(__FILE__, __LINE__);
    }
}

void FileBuffer::putData(const uint8_t x, const unsigned int n)
{
    if (m_current + n <= m_buffer + m_size)
    {
        memset(m_current, x, n);
        m_current += n;
    }
    else
    {
        throw BufferFull(__FILE__, __LINE__);
    }
}

void FileBuffer::putBits(const unsigned int x, const unsigned int n)
{
    if (m_current + ((m_nextbit + n + 7)/8) <= m_buffer + m_size)
    {
        for (unsigned int i = 0; i < n; i++)
        {
            if (x & (1 << i))
            {
                *m_current |= (1 << m_nextbit);
            }
            else
            {
                *m_current &= ~(1 << m_nextbit);
            }
            m_nextbit++;
            if (m_nextbit > 7)
            {
                m_current++;
                m_nextbit = 0;
            }
        }
    }
    else
    {
        throw BufferFull(__FILE__, __LINE__);
    }
}
