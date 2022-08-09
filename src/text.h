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

#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>

#include "font.h"

typedef enum
{
    HA_LEFT,
    HA_CENTER,
    HA_RIGHT,
    HA_FILL
} HorizontalAlignment;

typedef enum
{
    VA_TOP,
    VA_CENTER,
    VA_BOTTOM
} VerticalAlignment;

class TextBlock
{
private:
    std::string m_words;
    int m_color;
    int m_shadow;
    int m_shadowXoff;
    int m_shadowYoff;
    bool m_italic;
public:
    TextBlock();
    TextBlock ( const std::string& s, int c, int sh, int shx, int shy, bool it );
    virtual ~TextBlock();
    void setColor ( int c );
    int getColor() const
    {
        return m_color;
    }
    void setShadow ( int sh );
    int getShadow() const
    {
        return m_shadow;
    }
    void setShadowXOff ( int shx );
    int getShadowXOff() const
    {
        return m_shadowXoff;
    }
    void setShadowYOff ( int shy );
    int getShadowYOff() const
    {
        return m_shadowYoff;
    }
    void setItalic ( bool it );
    int getItalic() const
    {
        return m_italic;
    }
    void setWords ( const std::string& s );
    const std::string& getWords() const;
    void addWords ( const std::string& s );
    void eraseWords ( unsigned int n );
    unsigned int getSize() const;
    int draw ( int x, int y, int w, int h, Font *f, int extraWhiteSpace = 0 ) const;
};

class TextLine
{
private:
    Font *m_font;
    std::vector<TextBlock> m_textBlocks;
    int m_indent;
    int m_width;
    void copyFirstWord ( std::string& s, std::string& word, int& wordWidth );
public:
    TextLine ( Font *f );
    virtual ~TextLine();
    void setIndent ( int i );
    void clear();
    void addWords ( TextBlock& tb, int w );
    int getWidth() const
    {
        return m_width;
    }
    void draw ( int x, int y, int w, int h, int extraWhiteSpace ) const;
};

class Paragraph
{
private:
    Font *m_font;
    std::vector<TextBlock> m_textBlocks;
    std::vector<TextLine> m_lines;
    HorizontalAlignment m_horAlign;
    VerticalAlignment m_vertAlign;
    int m_indent;
public:
    Paragraph ( Font *f );
    virtual ~Paragraph();
    unsigned int getSize() const;
    const std::vector<TextLine>& getLines() const;
    void clear();
    void addTextBlock ( const TextBlock& tb );
    void setAlignment ( const HorizontalAlignment ha, const VerticalAlignment va );
    void setIndent ( int i );
    void generateLines ( int width, int extraIndent );
    void draw ( int x, int &y, int w, int &h, unsigned int& l ) const;
};

class Text
{
private:
    std::vector<Paragraph> m_paragraphs;
    unsigned int m_currentParagraph;
    unsigned int m_currentLine;
public:
    Text();
    virtual ~Text();
    unsigned int getSize() const;
    void addParagraph ( const Paragraph& p );
    void generateLines ( int width, int initialIndent );
    void drawPage ( int x, int y, int w, int h );
    void drawScroll ( int x, int y, int w, int h );
};

#endif
