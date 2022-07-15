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
#include "imageresource.h"

ImageResource::ImageResource()
    : m_compression ( COMPRESSION_LZW )
    , m_numImages ( 0 )
    , m_images ()
{
}

ImageResource::~ImageResource()
{
    clear();
}

unsigned int ImageResource::getCompression() const
{
    return m_compression;
}

void ImageResource::setCompression ( const unsigned int c )
{
    m_compression = c;
}

unsigned int ImageResource::getNumImages() const
{
    return m_numImages;
}

Image * ImageResource::getImage ( unsigned int n ) const
{
    return m_images[n];
}

void ImageResource::clear()
{
    for ( std::vector<Image*>::iterator it = m_images.begin(); it != m_images.end(); ++it )
    {
        delete ( *it );
    }
    m_images.clear();
}

void ImageResource::load ( FileBuffer *buffer )
{
    try
    {
        clear();
        if ( buffer->getUint16LE() != 0x1066 )
        {
            throw DataCorruption ( __FILE__, __LINE__ );
        }
        m_compression = ( unsigned int ) buffer->getUint16LE();
        m_numImages = ( unsigned int ) buffer->getUint16LE();
        unsigned int *imageSize = new unsigned int[m_numImages];
        buffer->skip ( 2 );
        unsigned int size = buffer->getUint32LE();
        for ( unsigned int i = 0; i < m_numImages; i++ )
        {
            imageSize[i] = ( unsigned int ) buffer->getUint16LE();
            unsigned int flags = ( unsigned int ) buffer->getUint16LE();
            unsigned int width = ( unsigned int ) buffer->getUint16LE();
            unsigned int height = ( unsigned int ) buffer->getUint16LE();
            Image *img = new Image ( width, height, flags );
            m_images.push_back ( img );
        }
        FileBuffer *decompressed = new FileBuffer ( size );
        buffer->decompress ( decompressed, m_compression );
        for ( unsigned int i = 0; i < m_numImages; i++ )
        {
            FileBuffer *imageBuffer = new FileBuffer ( imageSize[i] );
            imageBuffer->fill ( decompressed );
            ( m_images[i] )->load ( imageBuffer );
            delete imageBuffer;
        }
        delete decompressed;
        delete[] imageSize;
    }
    catch ( Exception &e )
    {
        e.print ( "ImageResource::Load" );
        throw;
    }
}

unsigned int ImageResource::save ( FileBuffer *buffer )
{
    try
    {
        buffer->putUint16LE ( 0x1066 );
        buffer->putUint16LE ( m_compression );
        buffer->putUint16LE ( m_numImages );
        unsigned int *imageSize = new unsigned int[m_numImages];
        buffer->putUint16LE ( 0 );
        unsigned int size = m_numImages * 4000;
        FileBuffer *decompressed = new FileBuffer ( size );
        for ( unsigned int i = 0; i < m_numImages; i++ )
        {
            imageSize[i] = ( m_images[i] )->save ( decompressed );
        }
        size = decompressed->getBytesDone();
        buffer->putUint32LE ( size );
        decompressed->rewind();
        FileBuffer *compressed = new FileBuffer ( size );
        size = decompressed->compress ( compressed, m_compression );
        for ( unsigned int i = 0; i < m_numImages; i++ )
        {
            Image* img = m_images[i];
            buffer->putUint16LE ( imageSize[i] );
            buffer->putUint16LE ( img->getFlags() );
            buffer->putUint16LE ( img->getWidth() );
            buffer->putUint16LE ( img->getHeight() );
        }
        buffer->copyFrom ( compressed, size );
        delete compressed;
        delete decompressed;
        delete[] imageSize;
        return size;
    }
    catch ( Exception &e )
    {
        e.print ( "ImageResource::Save" );
        throw;
    }
}
