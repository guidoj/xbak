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

#include "containerwidget.h"

ContainerWidget::ContainerWidget(const Rectangle &r)
    : ActiveWidget(r, -1)
    , m_widgets()
    , m_activeWidgets()
    , m_currentActiveWidget()
{
    setFocusable(false);
}

ContainerWidget::~ContainerWidget()
{
    clear();
}

void
ContainerWidget::clear()
{
    for (std::list<Widget *>::iterator it = m_widgets.begin(); it != m_widgets.end(); ++it)
    {
        delete (*it);
    }
    m_widgets.clear();
    for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
    {
        delete (*it);
    }
    m_activeWidgets.clear();
}

void
ContainerWidget::addWidget(Widget *w)
{
    m_widgets.push_back(w);
}

void
ContainerWidget::addActiveWidget(ActiveWidget *aw)
{
    m_activeWidgets.push_back(aw);
    m_currentActiveWidget = m_activeWidgets.end();
}

void
ContainerWidget::removeWidget(Widget *w)
{
    m_widgets.remove(w);
}

void
ContainerWidget::removeActiveWidget(ActiveWidget *aw)
{
    m_activeWidgets.remove(aw);
    m_currentActiveWidget = m_activeWidgets.end();
}

void
ContainerWidget::DrawChildWidgets()
{
    for (std::list<Widget *>::iterator it = m_widgets.begin(); it != m_widgets.end(); ++it)
    {
        (*it)->draw();
    }
    for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
    {
        (*it)->draw();
    }
}

void
ContainerWidget::draw()
{
    if (isVisible())
    {
        DrawChildWidgets();
    }
}

void
ContainerWidget::nextWidget()
{
    if (isVisible())
    {
        if (m_activeWidgets.size() > 0)
        {
            do
            {
                if (m_currentActiveWidget != m_activeWidgets.end())
                {
                    m_currentActiveWidget++;
                }
                if (m_currentActiveWidget == m_activeWidgets.end())
                {
                    m_currentActiveWidget = m_activeWidgets.begin();
                }
            }
            while (!((*m_currentActiveWidget)->isVisible()) || !((*m_currentActiveWidget)->isFocusable()));
            (*m_currentActiveWidget)->focus();
        }
    }
}

void
ContainerWidget::previousWidget()
{
    if (isVisible())
    {
        if (m_activeWidgets.size() > 0)
        {
            do
            {
                if (m_currentActiveWidget == m_activeWidgets.begin())
                {
                    m_currentActiveWidget = m_activeWidgets.end();
                }
                m_currentActiveWidget--;
            }
            while (!((*m_currentActiveWidget)->isVisible()) || !((*m_currentActiveWidget)->isFocusable()));
            (*m_currentActiveWidget)->focus();
        }
    }
}

void
ContainerWidget::leftClick(const bool toggle)
{
    if (isVisible())
    {
        if ((m_activeWidgets.size() > 0) && (m_currentActiveWidget != m_activeWidgets.end()))
        {
            Rectangle r = (*m_currentActiveWidget)->getRectangle();
            (*m_currentActiveWidget)->leftClick(toggle, r.getXCenter(), r.getYCenter());
        }
    }
}

void
ContainerWidget::rightClick(const bool toggle)
{
    if (isVisible())
    {
        if ((m_activeWidgets.size() > 0) && (m_currentActiveWidget != m_activeWidgets.end()))
        {
            Rectangle r = (*m_currentActiveWidget)->getRectangle();
            (*m_currentActiveWidget)->rightClick(toggle, r.getXCenter(), r.getYCenter());
        }
    }
}

void
ContainerWidget::leftClick(const bool toggle, const int x, const int y)
{
    if (isVisible())
    {
        for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
        {
            if (((*it)->getRectangle().isInside(Vector2D(x, y))) || ((*it)->isDraggable() && !toggle))
            {
                (*it)->leftClick(toggle, x, y);
            }
        }
    }
}

void
ContainerWidget::rightClick(const bool toggle, const int x, const int y)
{
    if (isVisible())
    {
        for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
        {
            if (((*it)->getRectangle().isInside(Vector2D(x, y))) || ((*it)->isDraggable() && !toggle))
            {
                (*it)->rightClick(toggle, x, y);
            }
        }
    }
}

void
ContainerWidget::drag(const int x, const int y)
{
    if (isVisible())
    {
        for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
        {
            if (((*it)->getRectangle().isInside(Vector2D(x, y))) && (*it)->isDraggable())
            {
                (*it)->drag(x, y);
            }
        }
    }
}

void
ContainerWidget::drop(const int x, const int y)
{
    if (isVisible())
    {
        for (std::list<Widget *>::iterator it = m_widgets.begin(); it != m_widgets.end(); ++it)
        {
            if ((*it)->getRectangle().isInside(Vector2D(x, y)))
            {
                (*it)->drop(x, y);
            }
        }
        for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
        {
            if ((*it)->getRectangle().isInside(Vector2D(x, y)))
            {
                (*it)->drop(x, y);
            }
        }
    }
}

void
ContainerWidget::pointerOver(const int x, const int y)
{
    if (isVisible())
    {
        for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
        {
            if ((*it)->getRectangle().isInside(Vector2D(x, y)))
            {
                (*it)->leftClick(false, x, y);
            }
        }
    }
}

void
ContainerWidget::reset()
{
    if (isVisible())
    {
        for (std::list<ActiveWidget *>::iterator it = m_activeWidgets.begin(); it != m_activeWidgets.end(); ++it)
        {
            (*it)->reset();
        }
    }
}
