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
#include "mediatoolkit.h"
#include "text.h"
#include "widget.h"

TextBlock::TextBlock()
    : m_words()
    , m_color ( 0 )
    , m_shadow ( 0 )
    , m_shadowXoff ( 0 )
    , m_shadowYoff ( 0 )
    , m_italic ( false )
{
}

TextBlock::TextBlock ( const std::string& s, int c, int sh, int shx, int shy, bool it )
    : m_words ( s )
    , m_color ( c )
    , m_shadow ( sh )
    , m_shadowXoff ( shx )
    , m_shadowYoff ( shy )
    , m_italic ( it )
{
}

TextBlock::~TextBlock()
{
}

void TextBlock::setWords ( const std::string& s )
{
    m_words = s;
}

void TextBlock::setColor ( int c )
{
    m_color = c;
}

void TextBlock::setShadow ( int sh )
{
    m_shadow = sh;
}

void TextBlock::setShadowXOff ( int shx )
{
    m_shadowXoff = shx;
}

void TextBlock::setShadowYOff ( int shy )
{
    m_shadowYoff = shy;
}

void TextBlock::setItalic ( bool it )
{
    m_italic = it;
}

unsigned int TextBlock::getSize() const
{
    return m_words.size();
}

void TextBlock::addWords ( const std::string& s )
{
    m_words += s;
}

void TextBlock::eraseWords ( unsigned int n )
{
    m_words.erase ( 0, n );
}

const std::string& TextBlock::getWords() const
{
    return m_words;
}

int TextBlock::draw ( int x, int y, int w, int, Font* f, int extraWhiteSpace ) const
{
    if ( extraWhiteSpace < 0 )
    {
        extraWhiteSpace = 0;
    }
    unsigned int i = 1;
    int numSpaces = 0;
    while ( i < m_words.size() )
    {
        if ( ( m_words[i - 1] > ' ' ) && ( m_words[i] == ' ' ) )
        {
            numSpaces++;
        }
        i++;
    }
    int offset = 0;
    int extraOff = 0;
    int space = 0;
    bool prevWasWS = false;
    if ( ( m_shadow > NO_SHADOW ) && ( ( m_shadowXoff != 0 ) || ( m_shadowYoff != 0 ) ) )
    {
        i = 0;
        offset = 0;
        extraOff = 0;
        space = 0;
        prevWasWS = false;
        while ( ( i < m_words.size() ) && ( offset + extraOff + f->getWidth ( m_words[i] - f->getFirst() ) <= w ) )
        {
            if ( !prevWasWS && ( m_words[i] == ' ' ) )
            {
                space++;
                extraOff = ( int ) ( ( double ) extraWhiteSpace * ( double ) space / ( double ) numSpaces );
            }
            f->drawChar ( x + m_shadowXoff + offset + extraOff, y + m_shadowYoff, m_words[i], m_shadow, m_italic );
            offset += f->getWidth ( ( unsigned int ) m_words[i] - f->getFirst() );
            prevWasWS = m_words[i] == ' ';
            i++;
        }
    }
    i = 0;
    offset = 0;
    extraOff = 0;
    space = 0;
    prevWasWS = false;
    while ( ( i < m_words.size() ) && ( offset + extraOff + f->getWidth ( m_words[i] - f->getFirst() ) <= w ) )
    {
        if ( !prevWasWS && ( m_words[i] == ' ' ) )
        {
            space++;
            extraOff = ( int ) ( ( double ) extraWhiteSpace * ( double ) space / ( double ) numSpaces );
        }
        f->drawChar ( x + offset + extraOff, y, m_words[i], m_color, m_italic );
        offset += f->getWidth ( ( unsigned int ) m_words[i] - f->getFirst() );
        prevWasWS = m_words[i] == ' ';
        i++;
    }
    return offset + extraOff;
}

TextLine::TextLine ( Font *f )
    : m_font ( f )
    , m_textBlocks()
    , m_indent ( 0 )
    , m_width ( 0 )
{
}

TextLine::~TextLine()
{
    m_textBlocks.clear();
}

void TextLine::setIndent ( int i )
{
    m_indent = i;
}

void TextLine::clear()
{
    m_textBlocks.clear();
    m_width = 0;
}

void TextLine::copyFirstWord ( std::string& s, std::string& word, int& wordWidth )
{
    wordWidth = 0;
    if ( s[0] == ' ' )
    {
        wordWidth += m_font->getWidth ( s[0] - m_font->getFirst() );
        s.erase ( 0, 1 );
    }
    unsigned int i = 0;
    while ( ( i < s.size() ) && ( s[i] > ' ' ) )
    {
        wordWidth += m_font->getWidth ( s[i] - m_font->getFirst() );
        i++;
    }
    word = s.substr ( 0, i );
}

void TextLine::addWords ( TextBlock& tb, int w )
{
    std::string words = tb.getWords();
    std::string word;
    int wordWidth = 0;
    TextBlock tmp ( "", tb.getColor(), tb.getShadow(), tb.getShadowXOff(), tb.getShadowYOff(), tb.getItalic() );
    bool isFirstWord = true;
    while ( ( !words.empty() ) && ( ( m_width + wordWidth ) <= w ) )
    {
        copyFirstWord ( words, word, wordWidth );
        if ( ( m_width + wordWidth ) <= w )
        {
            if ( !isFirstWord )
            {
                tmp.addWords ( " " );
                tb.eraseWords ( 1 );
            }
            tmp.addWords ( word );
            words.erase ( 0, word.size() );
            tb.eraseWords ( word.size() );
            m_width += wordWidth;
            wordWidth = 0;
            isFirstWord = false;
        }
    }
    m_textBlocks.push_back ( tmp );
}

void TextLine::draw ( int x, int y, int w, int h, int extraWhiteSpace ) const
{
    int xoff = m_indent;
    for ( unsigned int i = 0; i < m_textBlocks.size(); i++ )
    {
        xoff = m_textBlocks[i].draw ( x + xoff, y, w - xoff, h, m_font, extraWhiteSpace - xoff);
    }
}


Paragraph::Paragraph ( Font *f )
    : m_font ( f )
    , m_textBlocks()
    , m_lines()
    , m_horAlign ( HA_LEFT )
    , m_vertAlign ( VA_TOP )
    , m_indent ( 0 )
{
}

Paragraph::~Paragraph()
{
    m_textBlocks.clear();
    m_lines.clear();
}

unsigned int Paragraph::getSize() const
{
    return m_textBlocks.size();
}

const std::vector< TextLine >& Paragraph::getLines() const
{
    return m_lines;
}

void Paragraph::clear()
{
    m_textBlocks.clear();
    m_lines.clear();
}

void Paragraph::addTextBlock ( const TextBlock& tb )
{
    m_textBlocks.push_back ( tb );
}

void Paragraph::setAlignment ( const HorizontalAlignment ha, const VerticalAlignment va )
{
    m_horAlign = ha;
    m_vertAlign = va;
}

void Paragraph::generateLines ( int width, int extraIndent )
{
    m_lines.clear();
    int lineIndent = m_indent + extraIndent;
    TextLine line ( m_font );
    line.setIndent ( lineIndent );
    for ( unsigned int i = 0; i < m_textBlocks.size(); i++ )
    {
        TextBlock tb = m_textBlocks[i];
        while ( tb.getSize() > 0 )
        {
            line.addWords ( tb, width - lineIndent );
            if ( ( line.getWidth() > 0 ) && ( tb.getSize() > 0 ) )
            {
                m_lines.push_back ( line );
                line.clear();
                lineIndent = 0;
                line.setIndent ( lineIndent );
                if ( tb.getWords() [0] == ' ' )
                {
                    tb.eraseWords ( 1 );
                }
            }
        }
    }
    if ( line.getWidth() > 0 )
    {
        m_lines.push_back ( line );
    }
}

void Paragraph::setIndent ( int i )
{
    m_indent = i;
}

void Paragraph::draw ( int x, int &y, int w, int &h, unsigned int& l ) const
{
    while ( ( h >= m_font->getHeight() ) && ( l < m_lines.size() ) )
    {
        int xoff = 0;
        int extraWS = 0;
        if ( ( ( l + 1 ) < m_lines.size() ) && ( m_lines[l + 1].getWidth() > 0 ) )
        {
            switch ( m_horAlign )
            {
            case HA_LEFT:
                xoff = 0;
                extraWS = 0;
                break;
            case HA_CENTER:
                xoff = ( w - m_lines[l].getWidth() ) / 2;
                extraWS = 0;
                break;
            case HA_RIGHT:
                xoff = w - m_lines[l].getWidth();
                extraWS = 0;
                break;
            case HA_FILL:
                xoff = 0;
                extraWS = w - m_lines[l].getWidth();
                break;
            }
        }
        m_lines[l].draw ( x + xoff, y, w, m_font->getHeight(), extraWS );
        l++;
        y += m_font->getHeight();
        h -= m_font->getHeight();
    }
    if ( h < m_font->getHeight() )
    {
        h = 0;
    }
}


Text::Text()
    : m_paragraphs()
    , m_currentParagraph ( 0 )
    , m_currentLine ( 0 )
{
}

Text::~Text()
{
    m_paragraphs.clear();
}

unsigned int Text::getSize() const
{
    return m_paragraphs.size();
}

void Text::addParagraph ( const Paragraph& p )
{
    m_paragraphs.push_back ( p );
}

void Text::generateLines ( int width, int initialIndent )
{
    for ( unsigned int i = 0; i < m_paragraphs.size(); i++ )
    {
        m_paragraphs[i].generateLines ( width, initialIndent );
        initialIndent = 0;
    }
    m_currentParagraph = 0;
    m_currentLine = 0;
}

void Text::drawPage ( int x, int y, int w, int h )
{
    while ( ( h > 0 ) && ( m_currentParagraph < m_paragraphs.size() ) )
    {
        Paragraph p = m_paragraphs[m_currentParagraph];
        p.draw ( x, y, w, h, m_currentLine );
        if ( m_currentLine >= p.getLines().size() )
        {
            m_currentParagraph++;
            m_currentLine = 0;
            h -= 4;
            y += 4;
        }
    }
}

void Text::drawScroll ( int, int, int, int )
{
}
