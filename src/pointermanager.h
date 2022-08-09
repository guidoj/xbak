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

#ifndef POINTER_MANAGER_H
#define POINTER_MANAGER_H

#include "inventoryitemwidget.h"
#include "pointer.h"

const unsigned int NORMAL_POINTER = 0;
const unsigned int SPECIAL_POINTER = 1;

class PointerManager
    : public PointerButtonEventListener
    , public PointerMotionEventListener
{
private:
    unsigned int m_currentPointer;
    bool m_pressed;
    bool m_dragged;
    InventoryItemWidget *m_itemWidget;
    std::vector<Pointer *> m_pointerVec;
    std::list<DragEventListener *> m_dragListeners;
    static PointerManager *m_instance;

protected:
    PointerManager();

public:
    virtual ~PointerManager();
    static PointerManager* getInstance();
    static void cleanUp();
    Pointer* getCurrentPointer();
    void setCurrentPointer ( unsigned int n );
    InventoryItemWidget* getDraggedWidget ( void );
    void setDraggedWidget ( InventoryItemWidget *widget, const int x, const int y );
    void addPointer ( const std::string& resname );
    void pointerButtonPressed ( const PointerButtonEvent &pbe );
    void pointerButtonReleased ( const PointerButtonEvent &pbe );
    void pointerMoved ( const PointerMotionEvent &pme );
    void addDragListener ( DragEventListener *del );
    void removeDragListener ( DragEventListener *del );
};

#endif
