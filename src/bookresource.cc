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
#include "bookresource.h"

BookResource::BookResource()
    : m_pages()
{
}

BookResource::~BookResource()
{
    clear();
}

unsigned int BookResource::getSize() const
{
    return m_pages.size();
}

const PageData& BookResource::getPage ( const unsigned int i ) const
{
    return m_pages[i];
}

void BookResource::clear()
{
    m_pages.clear();
}

void BookResource::load ( FileBuffer *buffer )
{
    try
    {
        clear();
        buffer->skip ( 4 ); // file size
        unsigned int numPages = buffer->getUint16LE();
        unsigned int *pageOffset = new unsigned int [numPages];
        for ( unsigned int i = 0; i < numPages; i++ )
        {
            pageOffset[i] = buffer->getUint32LE();
        }
        for ( unsigned int i = 0; i < numPages; i++ )
        {
            buffer->seek ( 4 + pageOffset[i] );
            PageData pd;
            pd.xpos = buffer->getSint16LE();
            pd.ypos = buffer->getSint16LE();
            pd.width = buffer->getSint16LE();
            pd.height = buffer->getSint16LE();
            pd.number = buffer->getUint16LE();
            pd.id = buffer->getUint16LE();
            pd.prevId = buffer->getUint16LE();
            buffer->skip ( 2 );
            pd.nextId = buffer->getUint16LE();
            pd.flag = buffer->getUint16LE();
            unsigned int numDecorations = buffer->getUint16LE();
            unsigned int numFirstLetters = buffer->getUint16LE();
            pd.showNumber = buffer->getUint16LE() > 0;
            buffer->skip ( 30 );
            for ( unsigned int j = 0; j < numDecorations; j++ )
            {
                ImageInfo info;
                info.xpos = buffer->getSint16LE();
                info.ypos = buffer->getSint16LE();
                info.id = buffer->getUint16LE();
                info.flag = buffer->getUint16LE();
                pd.decorations.push_back ( info );
            }
            for ( unsigned int j = 0; j < numFirstLetters; j++ )
            {
                ImageInfo info;
                info.xpos = buffer->getSint16LE();
                info.ypos = buffer->getSint16LE();
                info.id = buffer->getUint16LE();
                info.flag = buffer->getUint16LE();
                pd.firstLetters.push_back ( info );
            }
            bool endOfPage = false;
            TextInfo ti;
            ti.paragraph = true;
            ti.italic = false;
            while ( !endOfPage && !buffer->atEnd() )
            {
                unsigned char c = buffer->getUint8();
                if ( ( c & 0xf0 ) == 0xf0 )
                {
                    switch ( c )
                    {
                    case 0xf0:
                        endOfPage = true;
                        break;
                    case 0xf1:
                        // end of paragraph
                        buffer->skip ( 16 );
                        break;
                    case 0xf2:
                        break;
                    case 0xf3:
                        break;
                    case 0xf4:
                        buffer->skip ( 8 );
                        switch ( buffer->getUint16LE() )
                        {
                        case 1:
                            ti.italic = false;
                            break;
                        case 5:
                            ti.italic = true;
                            break;
                        default:
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                    pd.textBlocks.push_back ( ti );
                    ti.italic = false;
                    ti.txt.clear();
                }
                else
                {
                    ti.txt.push_back ( c );
                }
            }
            pd.textBlocks.push_back ( ti );
            m_pages.push_back ( pd );
        }
        delete[] pageOffset;
    }
    catch ( Exception &e )
    {
        e.print ( "BookResource::Load" );
        throw;
    }
}

unsigned int BookResource::save ( FileBuffer *buffer )
{
    try
    {
        // TODO
        buffer = buffer;
        return 0;
    }
    catch ( Exception &e )
    {
        e.print ( "BookResource::Save" );
        throw;
    }
}
