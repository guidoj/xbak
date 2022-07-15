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

#ifndef CONTAINER_WIDGET_H
#define CONTAINER_WIDGET_H

#include "widget.h"

class ContainerWidget
    : public ActiveWidget
{
private:
    std::list<Widget *> m_widgets;
    std::list<ActiveWidget *> m_activeWidgets;
    std::list<ActiveWidget *>::iterator m_currentActiveWidget;
protected:
    void DrawChildWidgets();
public:
    ContainerWidget ( const Rectangle &r );
    virtual ~ContainerWidget();
    void draw();
    void clear();
    void addWidget ( Widget *w );
    void removeWidget ( Widget *w );
    void addActiveWidget ( ActiveWidget *aw );
    void removeActiveWidget ( ActiveWidget *aw );
    void nextWidget();
    void previousWidget();
    void leftClick ( const bool toggle );
    void rightClick ( const bool toggle );
    void leftClick ( const bool toggle, const int x, const int y );
    void rightClick ( const bool toggle, const int x, const int y );
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
    void pointerOver ( const int x, const int y );
    void reset();
};

#endif
