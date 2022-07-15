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

#include "exception.h"
#include "image.h"
#include "mediatoolkit.h"

const unsigned int FLAG_XYSWAPPED  = 0x20;
const unsigned int FLAG_UNKNOWN    = 0x40;
const unsigned int FLAG_COMPRESSED = 0x80;

Image::Image(const int w, const int h)
    : m_width(w)
    , m_height(h)
    , m_flags(0)
    , m_highres_lowcol(false)
    , m_pixel(0)
{
    if ((m_width > 0) && (m_height > 0))
    {
        m_pixel = new uint8_t[m_width * m_height];
        memset(m_pixel, 0, m_width * m_height);
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }
}

Image::Image(const int w, const int h, const unsigned int f)
    : m_width(w)
    , m_height(h)
    , m_flags(f)
    , m_highres_lowcol(false)
    , m_pixel(0)
{
    if ((m_width > 0) && (m_height > 0))
    {
        m_pixel = new uint8_t[m_width * m_height];
        memset(m_pixel, 0, m_width * m_height);
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }
}

Image::Image(const int w, const int h, const bool hrlc)
    : m_width(w)
    , m_height(h)
    , m_flags(0)
    , m_highres_lowcol(hrlc)
    , m_pixel(0)
{
    if ((m_width > 0) && (m_height > 0))
    {
        m_pixel = new uint8_t[m_width * m_height];
        memset(m_pixel, 0, m_width * m_height);
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }
}

Image::Image(const int w, const int h, const uint8_t *p)
    : m_width(w)
    , m_height(h)
    , m_flags(0)
    , m_highres_lowcol(false)
    , m_pixel(0)
{
    if ((m_width > 0) && (m_height > 0))
    {
        m_pixel = new uint8_t[m_width * m_height];
        memcpy(m_pixel, p, m_width * m_height);
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }
}

Image::Image(Image *img)
    : m_width(img->m_width)
    , m_height(img->m_height)
    , m_flags(img->m_flags)
    , m_highres_lowcol(img->m_highres_lowcol)
    , m_pixel(0)
{
    if ((m_width > 0) && (m_height > 0))
    {
        m_pixel = new uint8_t[m_width * m_height];
        memcpy(m_pixel, img->m_pixel, m_width * m_height);
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }
}

Image::Image(const int w, const int h, Image *img)
    : m_width(w)
    , m_height(h)
    , m_flags(img->m_flags)
    , m_highres_lowcol(img->m_highres_lowcol)
    , m_pixel(0)
{
    if ((m_width > 0) && (m_height > 0))
    {
        m_pixel = new uint8_t[m_width * m_height];
        uint8_t *p = m_pixel;
        double fx = (double)img->m_width / (double)m_width;
        double fy = (double)img->m_height / (double)m_height;
        for (int y = 0; y < m_height; y++)
        {
            uint8_t *prow = img->m_pixel + (int)(y * fy) * img->m_width;
            for (int x = 0; x < m_width; x++)
            {
                *p++ = *(prow + (int)(x * fx));
            }
        }
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }
}

Image::Image(const int w, const int h, std::vector<Image *> &img)
    : m_width(w)
    , m_height(h)
    , m_flags(img[0]->m_flags)
    , m_highres_lowcol(img[0]->m_highres_lowcol)
    , m_pixel(0)
{
    if ((m_width > 0) && (m_height > 0))
    {
        m_pixel = new uint8_t[m_width * m_height];
        uint8_t *p = m_pixel;
        if (m_width == img[0]->m_width)
        {
            unsigned int i = 0;
            int y = 0;
            do
            {
                uint8_t *q = img[i]->m_pixel + (y - i * m_width) * img[i]->m_width;
                memcpy(p, q, m_width);
                p += m_width;
                y++;
                if (y == m_height * ((int)i + 1))
                {
                    i++;
                    if (i == img.size())
                    {
                        i = 0;
                    }
                }
            }
            while (y < m_height);
        }
        if (m_height == img[0]->m_height)
        {
            for (int y = 0; y < m_height; y++)
            {
                unsigned int i = 0;
                int x = 0;
                do
                {
                    uint8_t *q = img[i]->m_pixel + y * img[i]->m_width;
                    memcpy(p, q, img[i]->m_width);
                    p += img[i]->m_width;
                    x += img[i]->m_width;
                    i++;
                    if (i == img.size())
                    {
                        i = 0;
                    }
                }
                while (x < m_width);
            }
        }
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }
}

Image::~Image()
{
    if (m_pixel)
    {
        delete [] m_pixel;
    }
}

int Image::getWidth() const
{
    return m_width;
}

int Image::getHeight() const
{
    return m_height;
}

unsigned int Image::getSize() const
{
    return (unsigned int)m_width * m_height;
}

unsigned int Image::getFlags() const
{
    return m_flags;
}

void Image::setFlags(const unsigned int f)
{
    m_flags = f;
}

bool Image::isHighResLowCol() const
{
    return m_highres_lowcol;
}

uint8_t Image::getPixel(const int x, const int y) const
{
    if ((m_pixel) && (x >= 0) && (x < m_width) && (y >= 0) && (y < m_height))
    {
        return m_pixel[x + m_width * y];
    }
    return 0;
}

uint8_t * Image::getPixels() const
{
    return m_pixel;
}

void Image::setPixel(const int x, const int y, const uint8_t color)
{
    if ((m_pixel) && (x >= 0) && (x < m_width) && (y >= 0) && (y < m_height))
    {
        m_pixel[x + m_width * y] = color;
    }
}

void Image::setPixels(uint8_t *data, unsigned int size)
{
    if ((m_pixel) && (data))
    {
        if (size == 0)
        {
            size = (unsigned int)m_width * m_height;
        }
        memcpy(m_pixel, data, size);
    }
}

void Image::fill(const uint8_t color)
{
    if (m_pixel)
    {
        memset(m_pixel, color, m_width * m_height);
    }
}

void Image::horizontalFlip()
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width / 2; x++)
        {
            uint8_t h = m_pixel[x + m_width * y];
            m_pixel[x + m_width * y] = m_pixel[m_width - x - 1 + m_width * y];
            m_pixel[m_width - x - 1 + m_width * y] = h;
        }
    }
}

void Image::verticalFlip()
{
    uint8_t *row = new uint8_t[m_width];
    for (int y = 0; y < m_height / 2; y++)
    {
        memcpy(row, m_pixel + m_width * y, m_width);
        memcpy(m_pixel + m_width * y, m_pixel + m_width * (m_height - y - 1), m_width);
        memcpy(m_pixel + m_width * (m_height - y - 1), row, m_width);
    }
    delete[] row;
}

void Image::load(FileBuffer *buffer)
{
    try
    {
        if (m_pixel)
        {
            FileBuffer *imgbuf;
            if (m_flags & FLAG_COMPRESSED)
            {
                imgbuf = new FileBuffer(m_width * m_height);
                buffer->decompressRLE(imgbuf);
            }
            else
            {
                imgbuf = buffer;
            }
            if (m_flags & FLAG_XYSWAPPED)
            {
                for (int x = 0; x < m_width; x++)
                {
                    for (int y = 0; y < m_height; y++)
                    {
                        setPixel(x, y, imgbuf->getUint8());
                    }
                }
            }
            else
            {
                if (m_highres_lowcol)
                {
                    for (int y = 0; y < m_height; y++)
                    {
                        for (int x = 0; x < m_width; x++)
                        {
                            uint8_t c = imgbuf->getUint8();
                            setPixel(x, y, (c & 0xf0) >> 4);
                            x++;
                            setPixel(x, y, c & 0x0f);
                        }
                    }
                }
                else
                {
                    imgbuf->getData(m_pixel, m_width * m_height);
                }
            }
            if (m_flags & FLAG_COMPRESSED)
            {
                delete imgbuf;
            }
        }
    }
    catch (Exception &e)
    {
        e.print("Image::Load");
        throw;
    }
}

unsigned int Image::save(FileBuffer *buffer)
{
    try
    {
        if (m_pixel)
        {
            FileBuffer *imgbuf = new FileBuffer(m_width * m_height);
            if (m_flags & FLAG_XYSWAPPED)
            {
                for (int x = 0; x < m_width; x++)
                {
                    for (int y = 0; y < m_height; y++)
                    {
                        imgbuf->putUint8(getPixel(x, y));
                    }
                }
            }
            else
            {
                if (m_highres_lowcol)
                {
                    for (int y = 0; y < m_height; y++)
                    {
                        for (int x = 0; x < m_width; x++)
                        {
                            uint8_t c1 = getPixel(x, y);
                            x++;
                            uint8_t c2 = getPixel(x, y);
                            imgbuf->putUint8(((c1 & 0x0f) << 4) | (c2 & 0x0f));
                        }
                    }
                }
                else
                {
                    imgbuf->putData(m_pixel, m_width * m_height);
                }
            }
            imgbuf->rewind();
            unsigned int size;
            if (m_flags & FLAG_COMPRESSED)
            {
                FileBuffer *compressed = new FileBuffer(m_width * m_height);
                size = imgbuf->compressRLE(compressed);
                buffer->copyFrom(compressed, size);
                delete compressed;
            }
            else
            {
                size = m_width * m_height;
                buffer->copyFrom(imgbuf, size);
            }
            delete imgbuf;
            return size;
        }
        return 0;
    }
    catch (Exception &e)
    {
        e.print("Image::Save");
        throw;
    }
    return 0;
}

void Image::read(const int x, const int y)
{
    MediaToolkit::getInstance()->getVideo()->readImage(x, y, m_width, m_height, m_pixel);
}

void Image::draw(const int x, const int y) const
{
    MediaToolkit::getInstance()->getVideo()->drawImage(x, y, m_width, m_height, m_pixel);
}

void Image::draw(const int x, const int y, const uint8_t transparent) const
{
    MediaToolkit::getInstance()->getVideo()->drawImage(x, y, m_width, m_height, m_pixel, transparent);
}

void Image::draw(const int x, const int y, const int xoff, const int yoff, const int w, const int h) const
{
    MediaToolkit::getInstance()->getVideo()->drawImage(x, y, m_width, m_height, xoff, yoff, w, h, m_pixel);
}

void Image::draw(const int x, const int y, const int xoff, const int yoff, const int w, const int h, const uint8_t transparent) const
{
    MediaToolkit::getInstance()->getVideo()->drawImage(x, y, m_width, m_height, xoff, yoff, w, h, m_pixel, transparent);
}
