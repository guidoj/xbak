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

#include "bmp.h"
#include "exception.h"
#include "filebuffer.h"

typedef struct _BitmapFileHeader
{
    char magic[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
}
BitmapFileHeader;

typedef struct _BitmapInfoHeader
{
    uint32_t infoSize;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xPelsPerMeter;
    uint32_t yPelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
}
BitmapInfoHeader;

const unsigned int BITMAP_FILE_HEADER_SIZE = 14;
const unsigned int BITMAP_INFO_HEADER_SIZE = 40;

BMP::BMP()
    : m_image(0)
    , m_palette(0)
{
}

BMP::~BMP()
{
}

Image * BMP::getImage() const
{
    return m_image;
}

void BMP::setImage(Image *img)
{
    m_image = img;
}

Palette * BMP::getPalette() const
{
    return m_palette;
}

void BMP::setPalette(Palette *pal)
{
    m_palette = pal;
}

void BMP::load(const std::string &name)
{
    std::ifstream ifs;
    ifs.open(name.c_str(), std::ios::in | std::ios::binary);
    if (ifs.fail())
    {
        throw OpenError(__FILE__, __LINE__, "(" + name + ")");
    }

    FileBuffer bmpFileHdrBuffer(BITMAP_FILE_HEADER_SIZE);
    bmpFileHdrBuffer.load(ifs);
    BitmapFileHeader bmpFileHdr;
    bmpFileHdrBuffer.getData(bmpFileHdr.magic, 2);
    bmpFileHdr.fileSize = bmpFileHdrBuffer.getUint32LE();
    bmpFileHdr.reserved1 = bmpFileHdrBuffer.getUint16LE();
    bmpFileHdr.reserved2 = bmpFileHdrBuffer.getUint16LE();
    bmpFileHdr.offset = bmpFileHdrBuffer.getUint32LE();
    if ((bmpFileHdr.magic[0] != 'B') || (bmpFileHdr.magic[1] != 'M'))
    {
        throw DataCorruption(__FILE__, __LINE__, "BMP magic");
    }

    FileBuffer bmpInfoHdrBuffer(BITMAP_INFO_HEADER_SIZE);
    bmpInfoHdrBuffer.load(ifs);
    BitmapInfoHeader bmpInfoHdr;
    bmpInfoHdr.infoSize = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.width = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.height = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.planes = bmpInfoHdrBuffer.getUint16LE();
    bmpInfoHdr.bitCount = bmpInfoHdrBuffer.getUint16LE();
    bmpInfoHdr.compression = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.imageSize = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.xPelsPerMeter = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.yPelsPerMeter = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.colorsUsed = bmpInfoHdrBuffer.getUint32LE();
    bmpInfoHdr.colorsImportant = bmpInfoHdrBuffer.getUint32LE();
    if (bmpInfoHdr.infoSize != BITMAP_INFO_HEADER_SIZE)
    {
        throw DataCorruption(__FILE__, __LINE__, "BMP info header size");
    }
    if (bmpInfoHdr.planes != 1)
    {
        throw DataCorruption(__FILE__, __LINE__, "BMP planes");
    }
    if (bmpInfoHdr.compression != 0)
    {
        throw DataCorruption(__FILE__, __LINE__, "BMP compression");
    }

    if (!m_palette)
    {
        throw NullPointer(__FILE__, __LINE__, "palette");
    }
    FileBuffer paletteBuffer(bmpInfoHdr.colorsUsed * 4);
    paletteBuffer.load(ifs);
    if (m_palette->getSize() != bmpInfoHdr.colorsUsed)
    {
        throw DataCorruption(__FILE__, __LINE__, "palette size");
    }
    for (unsigned int i = 0; i < bmpInfoHdr.colorsUsed; i++)
    {
        Color c;
        c.b = paletteBuffer.getUint8();
        c.g = paletteBuffer.getUint8();
        c.r = paletteBuffer.getUint8();
        c.a = paletteBuffer.getUint8();
        m_palette->setColor(i, c);
    }

    if (!m_image)
    {
        throw NullPointer(__FILE__, __LINE__, "image");
    }
    FileBuffer imageBuffer(bmpInfoHdr.imageSize);
    imageBuffer.load(ifs);
    if ((m_image->getWidth() != bmpInfoHdr.width) || (m_image->getHeight() != bmpInfoHdr.height))
    {
        throw DataCorruption(__FILE__, __LINE__, "image size");
    }
    uint8_t *pixelLine = m_image->getPixels() + bmpInfoHdr.imageSize;
    while (pixelLine > m_image->getPixels())
    {
        pixelLine -= bmpInfoHdr.width;
        imageBuffer.getData(pixelLine, bmpInfoHdr.width);
    }

    ifs.close();
}

void BMP::save(const std::string &name)
{
    std::ofstream ofs;

    ofs.open(name.c_str(), std::ios::out | std::ios::binary);
    if (ofs.fail())
    {
        throw OpenError(__FILE__, __LINE__, "(" + name + ")");
    }

    BitmapFileHeader bmpFileHdr;
    bmpFileHdr.magic[0] = 'B';
    bmpFileHdr.magic[1] = 'M';
    bmpFileHdr.fileSize = BITMAP_FILE_HEADER_SIZE + BITMAP_INFO_HEADER_SIZE + m_palette->getSize() * 4 + m_image->getSize();
    bmpFileHdr.reserved1 = 0;
    bmpFileHdr.reserved2 = 0;
    bmpFileHdr.offset = BITMAP_FILE_HEADER_SIZE + BITMAP_INFO_HEADER_SIZE + m_palette->getSize() * 4;
    FileBuffer bmpFileHdrBuffer(BITMAP_FILE_HEADER_SIZE);
    bmpFileHdrBuffer.putData(bmpFileHdr.magic, 2);
    bmpFileHdrBuffer.putUint32LE(bmpFileHdr.fileSize);
    bmpFileHdrBuffer.putUint16LE(bmpFileHdr.reserved1);
    bmpFileHdrBuffer.putUint16LE(bmpFileHdr.reserved2);
    bmpFileHdrBuffer.putUint32LE(bmpFileHdr.offset);
    bmpFileHdrBuffer.save(ofs);

    BitmapInfoHeader bmpInfoHdr;
    bmpInfoHdr.infoSize = BITMAP_INFO_HEADER_SIZE;
    bmpInfoHdr.width = m_image->getWidth();
    bmpInfoHdr.height = m_image->getHeight();
    bmpInfoHdr.planes = 1;
    bmpInfoHdr.bitCount = WINDOW_BPP;
    bmpInfoHdr.compression = 0;
    bmpInfoHdr.imageSize = m_image->getSize();
    bmpInfoHdr.xPelsPerMeter = 0;
    bmpInfoHdr.yPelsPerMeter = 0;
    bmpInfoHdr.colorsUsed = m_palette->getSize();
    bmpInfoHdr.colorsImportant = 0;
    FileBuffer bmpInfoHdrBuffer(BITMAP_INFO_HEADER_SIZE);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.infoSize);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.width);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.height);
    bmpInfoHdrBuffer.putUint16LE(bmpInfoHdr.planes);
    bmpInfoHdrBuffer.putUint16LE(bmpInfoHdr.bitCount);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.compression);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.imageSize);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.xPelsPerMeter);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.yPelsPerMeter);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.colorsUsed);
    bmpInfoHdrBuffer.putUint32LE(bmpInfoHdr.colorsImportant);
    bmpInfoHdrBuffer.save(ofs);

    FileBuffer paletteBuffer(m_palette->getSize() * 4);
    for (unsigned int i = 0; i < m_palette->getSize(); i++)
    {
        Color c = m_palette->getColor(i);
        paletteBuffer.putUint8(c.b);
        paletteBuffer.putUint8(c.g);
        paletteBuffer.putUint8(c.r);
        paletteBuffer.putUint8(c.a);
    }
    paletteBuffer.save(ofs);

    FileBuffer imageBuffer(m_image->getSize());
    uint8_t *pixelLine = m_image->getPixels() + m_image->getSize();
    while (pixelLine > m_image->getPixels())
    {
        pixelLine -= m_image->getWidth();
        imageBuffer.putData(pixelLine, m_image->getWidth());
    }
    imageBuffer.save(ofs);

    ofs.close();
}
