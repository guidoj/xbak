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

#include "imageresource.h"
#include "mediatoolkit.h"
#include "pointermanager.h"

PointerManager* PointerManager::m_instance = 0;

PointerManager::PointerManager()
    : m_currentPointer(0)
    , m_pressed(false)
    , m_dragged(false)
    , m_itemWidget(0)
    , m_pointerVec()
    , m_dragListeners()
{
    MediaToolkit::getInstance()->addPointerButtonListener(this);
    MediaToolkit::getInstance()->addPointerMotionListener(this);
}

PointerManager::~PointerManager()
{
    MediaToolkit::getInstance()->removePointerButtonListener(this);
    MediaToolkit::getInstance()->removePointerMotionListener(this);
    for (unsigned int i = 0; i < m_pointerVec.size(); i++)
    {
        delete m_pointerVec[i];
    }
    m_pointerVec.clear();
    m_dragListeners.clear();
}

PointerManager*
PointerManager::getInstance()
{
    if (!m_instance)
    {
        m_instance = new PointerManager();
    }
    return m_instance;
}

void
PointerManager::cleanUp()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = 0;
    }
}

Pointer*
PointerManager::getCurrentPointer()
{
    return m_pointerVec[m_currentPointer];
}

void
PointerManager::setCurrentPointer(const unsigned int n)
{
    if (n < m_pointerVec.size())
    {
        m_currentPointer = n;
    }
    else
    {
        m_currentPointer = 0;
    }
}

InventoryItemWidget*
PointerManager::getDraggedWidget()
{
    return m_itemWidget;
}

void
PointerManager::setDraggedWidget(InventoryItemWidget *widget, const int x, const int y)
{
    if (m_itemWidget && (m_itemWidget != widget))
    {
        m_itemWidget->setDragged(false);
    }
    m_itemWidget = widget;
    if (widget)
    {
        m_pointerVec[m_currentPointer]->setDragImage(widget->getImage(), x, y);
    }
    else
    {
        m_pointerVec[m_currentPointer]->setDragImage(0, x, y);
    }
}

void
PointerManager::addPointer(const std::string& resname)
{
    Pointer *mp = new Pointer(resname);
    m_pointerVec.push_back(mp);
}

void
PointerManager::pointerButtonPressed(const PointerButtonEvent &pbe)
{
    m_pointerVec[m_currentPointer]->setPosition(pbe.getXPos(), pbe.getYPos());
    if ((!m_pressed) && (pbe.getButton() == PB_PRIMARY))
    {
        m_pressed = true;
    }
}

void
PointerManager::pointerButtonReleased(const PointerButtonEvent &pbe)
{
    m_pointerVec[m_currentPointer]->setPosition(pbe.getXPos(), pbe.getYPos());
    if ((m_pressed) && (pbe.getButton() == PB_PRIMARY))
    {
        m_pressed = false;
        if (m_dragged)
        {
            m_dragged = false;
            DragEvent de(m_dragged, pbe.getXPos(), pbe.getYPos());
            for (std::list<DragEventListener *>::iterator it = m_dragListeners.begin(); it != m_dragListeners.end(); ++it)
            {
                (*it)->pointerDragged(de);
            }
        }
    }
}

void
PointerManager::pointerMoved(const PointerMotionEvent &pme)
{
    m_pointerVec[m_currentPointer]->setPosition(pme.getXPos(), pme.getYPos());
    if ((m_pressed) && (!m_dragged))
    {
        m_dragged = true;
        DragEvent de(m_dragged, pme.getXPos(), pme.getYPos());
        for (std::list<DragEventListener *>::iterator it = m_dragListeners.begin(); it != m_dragListeners.end(); ++it)
        {
            (*it)->pointerDragged(de);
        }
    }
}

void
PointerManager::addDragListener(DragEventListener *del)
{
    m_dragListeners.push_back(del);
}

void
PointerManager::removeDragListener(DragEventListener *del)
{
    m_dragListeners.remove(del);
}
