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

#include "mediatoolkit.h"
#include "widget.h"

Widget::Widget(const Rectangle &r)
    : m_rect(r)
    , m_visible(true)
{
}

Widget::~Widget()
{
}

const Rectangle& Widget::getRectangle() const
{
    return m_rect;
}

void Widget::setPosition(const int x, const int y)
{
    m_rect.setXPos(x);
    m_rect.setYPos(y);
}

void Widget::setVisible(const bool toggle)
{
    m_visible = toggle;
}

bool Widget::isVisible() const
{
    return m_visible;
}


ActiveWidget::ActiveWidget(const Rectangle &r, const int a)
    : Widget(r)
    , m_action(a)
    , m_draggable(false)
    , m_focusable(true)
    , m_actionListeners()
{
}

ActiveWidget::~ActiveWidget()
{
    m_actionListeners.clear();
}

int ActiveWidget::getAction() const
{
    return m_action;
}

bool ActiveWidget::isDraggable() const
{
    return m_draggable;
}

void ActiveWidget::setDraggable(const bool toggle)
{
    m_draggable = toggle;
}

bool ActiveWidget::isFocusable() const
{
    return m_focusable;
}

void ActiveWidget::setFocusable(const bool toggle)
{
    m_focusable = toggle;
}

void ActiveWidget::generateActionEvent(const int a)
{
    ActionEvent ae(a, m_rect.getXCenter(), m_rect.getYCenter());
    for (std::list<ActionEventListener *>::iterator it = m_actionListeners.begin(); it != m_actionListeners.end(); ++it)
    {
        (*it)->actionPerformed(ae);
    }
}

void ActiveWidget::generateActionEvent(const int a, const int x, const int y)
{
    ActionEvent ae(a, x, y);
    for (std::list<ActionEventListener *>::iterator it = m_actionListeners.begin(); it != m_actionListeners.end(); ++it)
    {
        (*it)->actionPerformed(ae);
    }
}

void ActiveWidget::generateActionEvent(const ActionEvent& ae)
{
    for (std::list<ActionEventListener *>::iterator it = m_actionListeners.begin(); it != m_actionListeners.end(); ++it)
    {
        (*it)->actionPerformed(ae);
    }
}

void ActiveWidget::addActionListener(ActionEventListener *ael)
{
    m_actionListeners.push_back(ael);
}

void ActiveWidget::removeActionListener(ActionEventListener *ael)
{
    m_actionListeners.remove(ael);
}

void ActiveWidget::focus()
{
    if (m_focusable)
    {
        MediaToolkit::getInstance()->setPointerPosition(m_rect.getXPos() + m_rect.getWidth() / 2, m_rect.getYPos() + m_rect.getHeight() / 2);
    }
}

void ActiveWidget::reset()
{
}
