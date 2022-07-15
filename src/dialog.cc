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

#include "exception.h"
#include "dialog.h"
#include "pointermanager.h"
#include "requestresource.h"

Dialog::Dialog(Palette *pal, DialogWindow *dialogWin)
    : m_window(dialogWin)
    , m_palette(pal)
    , m_action(0)
    , m_running(false)
{
    try
    {
        PointerManager::getInstance()->setCurrentPointer(NORMAL_POINTER);
        PointerManager::getInstance()->getCurrentPointer()->setVisible(true);
    }
    catch (Exception &e)
    {
        e.print("Dialog::Dialog");
        throw;
    }
}

Dialog::~Dialog()
{
    // palette gets deleted elsewhere
    if (m_window)
    {
        delete m_window;
    }
}

void Dialog::enter()
{
    try
    {
        MediaToolkit* media = MediaToolkit::getInstance();
        PointerManager *pointerManager = PointerManager::getInstance();
        media->getVideo()->clear();
        pointerManager->getCurrentPointer()->attach(this);
        m_window->fadeIn(m_palette);
        media->addKeyboardListener(this);
        media->addPointerButtonListener(this);
        pointerManager->addDragListener(this);
    }
    catch (Exception &e)
    {
        e.print("Dialog::Enter");
        throw;
    }
}

void Dialog::leave()
{
    try
    {
        MediaToolkit* media = MediaToolkit::getInstance();
        PointerManager *pointerManager = PointerManager::getInstance();
        m_window->fadeOut(m_palette);
        const Rectangle r = m_window->getRectangle();
        m_window->pointerOverWidget(r.getWidth(), r.getHeight());
        pointerManager->removeDragListener(this);
        media->removePointerButtonListener(this);
        media->removeKeyboardListener(this);
        pointerManager->getCurrentPointer()->detach(this);
        media->getVideo()->clear();
    }
    catch (Exception &e)
    {
        e.print("Dialog::Leave");
        throw;
    }
}

int Dialog::execute()
{
    try
    {
        m_running = true;
        while (m_running)
        {
            MediaToolkit::getInstance()->pollEvents();
        }
        return m_action;
    }
    catch (Exception &e)
    {
        e.print("Dialog::Execute");
        throw;
    }
}

void Dialog::update()
{
    m_window->draw();
}

void Dialog::pointerButtonPressed(const PointerButtonEvent& pbe)
{
    if (m_running)
    {
        switch (pbe.getButton())
        {
        case PB_PRIMARY:
            m_window->leftClickWidget(true, pbe.getXPos(), pbe.getYPos());
            break;
        case PB_SECONDARY:
            m_window->rightClickWidget(true, pbe.getXPos(), pbe.getYPos());
            break;
        default:
            break;
        }
    }
    m_window->draw();
}

void Dialog::pointerButtonReleased(const PointerButtonEvent& pbe)
{
    switch (pbe.getButton())
    {
    case PB_PRIMARY:
        m_window->leftClickWidget(false, pbe.getXPos(), pbe.getYPos());
        break;
    case PB_SECONDARY:
        m_window->rightClickWidget(false, pbe.getXPos(), pbe.getYPos());
        break;
    default:
        break;
    }
    m_window->draw();
}

void Dialog::actionPerformed(const ActionEvent& ae)
{
    m_action = ae.getAction();
    m_running = false;
}

void Dialog::pointerDragged(const DragEvent& de)
{
    if (m_running)
    {
        if (de.getToggle())
        {
            m_window->dragWidget(de.getXPos(), de.getYPos());
        }
        else
        {
            m_window->dropWidget(de.getXPos(), de.getYPos());
        }
    }
    m_window->draw();
}


GameDialog::GameDialog(Palette *pal, DialogWindow *dialogwin)
    : Dialog(pal, dialogwin)
{
}

GameDialog::~GameDialog()
{
}

void GameDialog::keyPressed(const KeyboardEvent& kbe)
{
    if (m_running)
    {
        switch (kbe.getKey())
        {
        case KEY_ESCAPE:
            m_action = ACT_ESCAPE;
            m_running = false;
            break;
        case KEY_TAB:
            m_window->selectNextWidget();
            break;
        case KEY_UP:
            m_action = ACT_UP;
            m_running = false;
            break;
        case KEY_DOWN:
            m_action = ACT_DOWN;
            m_running = false;
            break;
        case KEY_LEFT:
            m_action = ACT_LEFT;
            m_running = false;
            break;
        case KEY_RIGHT:
            m_action = ACT_RIGHT;
            m_running = false;
            break;
        default:
            break;
        }
    }
    m_window->draw();
}

void GameDialog::keyReleased(const KeyboardEvent& kbe)
{
    if (m_running)
    {
        switch (kbe.getKey())
        {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            m_action = ACT_STOP;
            m_running = false;
            break;
        default:
            break;
        }
    }
    m_window->draw();
}


OptionsDialog::OptionsDialog(Palette *pal, DialogWindow *dialogwin)
    : Dialog(pal, dialogwin)
{
}

OptionsDialog::~OptionsDialog()
{
}

void OptionsDialog::keyPressed(const KeyboardEvent& kbe)
{
    if (m_running)
    {
        switch (kbe.getKey())
        {
        case KEY_ESCAPE:
            m_action = ACT_ESCAPE;
            m_running = false;
            break;
        case KEY_DOWN:
        case KEY_TAB:
            m_window->selectNextWidget();
            break;
        case KEY_UP:
            m_window->selectPreviousWidget();
            break;
        case KEY_RETURN:
        case KEY_SPACE:
            m_window->leftClickWidget(true);
            break;
        default:
            break;
        }
    }
    m_window->draw();
}

void OptionsDialog::keyReleased(const KeyboardEvent& kbe)
{
    switch (kbe.getKey())
    {
    case KEY_RETURN:
    case KEY_SPACE:
        m_window->leftClickWidget(false);
        break;
    default:
        break;
    }
    m_window->draw();
}
