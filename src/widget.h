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

#ifndef WIDGET_H
#define WIDGET_H

#include <list>

#include "eventlistener.h"
#include "geometry.h"

const int NO_SHADOW            = -1;
const int COLOR_BLACK          = 0;
const int SHADOW_COLOR         = 1;
const int LIGHT_COLOR          = 4;
const int TEXT_COLOR_NORMAL    = 10;
const int TEXT_COLOR_DISABLED  = 11;
const int TEXT_COLOR_PRESSED   = 6;
const int BUTTON_COLOR_NORMAL  = 14;
const int BUTTON_COLOR_PRESSED = 11;
const int POPUP_COLOR          = 14;
const int INFO_TEXT_COLOR      = 159;

const int RIGHT_CLICK_OFFSET   = 256;
const int RELEASE_OFFSET       = 512;
const int INVENTORY_OFFSET     = 1024;

class Widget
{
protected:
    Rectangle m_rect;
    bool m_visible;
public:
    Widget ( const Rectangle &r );
    virtual ~Widget();
    const Rectangle& getRectangle() const;
    void setPosition ( const int x, const int y );
    void setVisible ( const bool toggle );
    bool isVisible() const;
    virtual void draw() = 0;
    virtual void drag ( const int x, const int y ) = 0;
    virtual void drop ( const int x, const int y ) = 0;
};

class ActiveWidget
    : public Widget
{
protected:
    int m_action;
    bool m_draggable;
    bool m_focusable;
    std::list<ActionEventListener *> m_actionListeners;
public:
    ActiveWidget ( const Rectangle &r, const int a );
    virtual ~ActiveWidget();
    int getAction() const;
    bool isDraggable() const;
    void setDraggable ( const bool toggle );
    bool isFocusable() const;
    void setFocusable ( const bool toggle );
    void addActionListener ( ActionEventListener *ael );
    void removeActionListener ( ActionEventListener *ael );
    void generateActionEvent ( const int a );
    void generateActionEvent ( const int a, const int x, const int y );
    void generateActionEvent ( const ActionEvent& ae );
    void focus();
    virtual void reset();
    virtual void leftClick ( const bool toggle, const int x, const int y ) = 0;
    virtual void rightClick ( const bool toggle, const int x, const int y ) = 0;
};

#endif
