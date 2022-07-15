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

#include "filemanager.h"
#include "pointer.h"

Pointer::Pointer(const std::string &resname)
    : Subject()
    , m_visible(false)
    , m_xPos(0)
    , m_yPos(0)
    , m_pointerType(PT_SWORD)
    , m_pointerImages()
    , m_dragImage(0)
    , m_dragOffsetX(0)
    , m_dragOffsetY(0)
{
    FileManager::getInstance()->load(&m_pointerImages, resname);
}

Pointer::~Pointer()
{}

int
Pointer::getXPos() const
{
    return m_xPos;
}

int
Pointer::getYPos() const
{
    return m_yPos;
}

void
Pointer::setPointerType(PointerType pt)
{
    m_pointerType = pt;
    notify();
}

void
Pointer::setPosition(const int x, const int y)
{
    m_xPos = x;
    m_yPos = y;
    notify();
}

void
Pointer::setVisible(const bool vis)
{
    m_visible = vis;
    notify();
}

void
Pointer::setDragImage(Image *img, const int x, const int y)
{
    m_dragImage = img;
    m_dragOffsetX = x;
    m_dragOffsetY = y;
}

void
Pointer::draw()
{
    if (m_visible)
    {
        if (m_dragImage)
        {
            m_dragImage->draw(m_xPos + m_dragOffsetX, m_yPos + m_dragOffsetY, 0);
        }
        m_pointerImages.getImage((int)m_pointerType)->draw(m_xPos, m_yPos, 0);
    }
}
