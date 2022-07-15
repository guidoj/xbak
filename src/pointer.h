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

#ifndef POINTER_H
#define POINTER_H

#include "eventlistener.h"
#include "imageresource.h"
#include "subject.h"
#include "video.h"

typedef enum _PointerType
{
    PT_SWORD = 0,
    PT_HAND = 1,
    PT_HOURGLASS = 2,
    PT_LOOKING_GLASS = 3,
    PT_EXIT = 4,
    PT_INN = 5,
    PT_TAVERN = 6,
    PT_SHOP = 7,
    PT_PALACE = 8,
    PT_TEMPLE = 9,
    PT_HOUSE = 10,
    PT_TELEPORT = 11,
    PT_PETITION = 12,
    PT_BARD = 13,
    PT_TALK = 14,
    PT_BUY_SELL = 15,
    PT_ENTER = 16,
    PT_REPAIR = 17,
    PT_BUY = 18,
    PT_HAND2 = 19,
    PT_GAB = 20,
    PT_CHAT = 21,
    PT_SEWER = 22,
    PT_BAR = 23,
    PT_BARMAID = 24,
    PT_BARKEEP = 25,
    PT_INNKEEPER = 26
} PointerType;

class Pointer
    : public Subject
{
private:
    bool m_visible;
    int m_xPos;
    int m_yPos;
    PointerType m_pointerType;
    ImageResource m_pointerImages;
    Image *m_dragImage;
    int m_dragOffsetX;
    int m_dragOffsetY;
public:
    Pointer ( const std::string &resname );
    virtual ~Pointer();
    int getXPos() const;
    int getYPos() const;
    void setPointerType ( PointerType pt );
    void setPosition ( const int x, const int y );
    void setVisible ( const bool vis );
    void setDragImage ( Image *img, const int x, const int y );
    void draw();
};

#endif

