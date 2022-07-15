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

#ifndef DIALOG_H
#define DIALOG_H

#include "dialogwindow.h"
#include "observer.h"

class Dialog
    : public ActionEventListener
    , public PointerButtonEventListener
    , public KeyboardEventListener
    , public DragEventListener
    , public Observer
{
protected:
    DialogWindow *m_window;
    Palette *m_palette;
    unsigned int m_action;
    bool m_running;
public:
    Dialog ( Palette *pal, DialogWindow *dialogwin );
    virtual ~Dialog();
    void enter();
    void leave();
    int execute();
    void update();
    void actionPerformed ( const ActionEvent& ae );
    void pointerButtonPressed ( const PointerButtonEvent& pbe );
    void pointerButtonReleased ( const PointerButtonEvent& pbe );
    void pointerDragged ( const DragEvent &de );
};

class GameDialog
    : public Dialog
{
public:
    GameDialog ( Palette *pal, DialogWindow *dialogwin );
    ~GameDialog();
    void keyPressed ( const KeyboardEvent& kbe );
    void keyReleased ( const KeyboardEvent& kbe );
};

class OptionsDialog
    : public Dialog
{
public:
    OptionsDialog ( Palette *pal, DialogWindow *dialogwin );
    ~OptionsDialog();
    void keyPressed ( const KeyboardEvent& kbe );
    void keyReleased ( const KeyboardEvent& kbe );
};

#endif
