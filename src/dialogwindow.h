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

#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include "palette.h"
#include "panelwidget.h"

class DialogWindow
{
private:
    PanelWidget *m_panel;
public:
    DialogWindow ( PanelWidget *panelwidget );
    virtual ~DialogWindow();
    const Rectangle& getRectangle() const;
    void draw();
    void fadeIn ( Palette* pal );
    void fadeOut ( Palette* pal );
    void leftClickWidget ( const bool toggle );
    void rightClickWidget ( const bool toggle );
    void leftClickWidget ( const bool toggle, const int x, const int y );
    void rightClickWidget ( const bool toggle, const int x, const int y );
    void dragWidget ( const int x, const int y );
    void dropWidget ( const int x, const int y );
    void pointerOverWidget ( const int x, const int y );
    void selectNextWidget();
    void selectPreviousWidget();
};

#endif
