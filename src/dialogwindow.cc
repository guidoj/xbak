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

#include "dialogwindow.h"
#include "pointermanager.h"

DialogWindow::DialogWindow(PanelWidget *panelwidget)
    : m_panel(panelwidget)
{
}

DialogWindow::~DialogWindow()
{
    if (m_panel)
    {
        delete m_panel;
    }
}

const Rectangle& DialogWindow::getRectangle() const
{
    return m_panel->getRectangle();
}

void DialogWindow::draw()
{
    m_panel->draw();
    PointerManager::getInstance()->getCurrentPointer()->draw();
    MediaToolkit::getInstance()->getVideo()->refresh();
}

void DialogWindow::fadeIn(Palette* pal)
{
    m_panel->reset();
    m_panel->draw();
    PointerManager::getInstance()->getCurrentPointer()->draw();
    pal->fadeIn(0, PALETTE_COLORS, 64, 5);
}

void DialogWindow::fadeOut(Palette* pal)
{
    m_panel->draw();
    PointerManager::getInstance()->getCurrentPointer()->draw();
    pal->fadeOut(0, PALETTE_COLORS, 64, 5);
}

void DialogWindow::leftClickWidget(const bool toggle)
{
    m_panel->leftClick(toggle);
}

void DialogWindow::rightClickWidget(const bool toggle)
{
    m_panel->rightClick(toggle);
}

void DialogWindow::leftClickWidget(const bool toggle, const int x, const int y)
{
    m_panel->leftClick(toggle, x, y);
}

void DialogWindow::rightClickWidget(const bool toggle, const int x, const int y)
{
    m_panel->rightClick(toggle, x, y);
}

void DialogWindow::dragWidget(const int x, const int y)
{
    m_panel->drag(x, y);
}

void DialogWindow::dropWidget(const int x, const int y)
{
    m_panel->drop(x, y);
    PointerManager::getInstance()->setDraggedWidget(0, 0, 0);
}

void DialogWindow::pointerOverWidget(const int x, const int y)
{
    m_panel->pointerOver(x, y);
}

void DialogWindow::selectNextWidget()
{
    m_panel->nextWidget();
}

void DialogWindow::selectPreviousWidget()
{
    m_panel->previousWidget();
}
