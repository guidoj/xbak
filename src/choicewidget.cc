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

#include "choicewidget.h"
#include "exception.h"
#include "mediatoolkit.h"
#include "preferencesdialogbridge.h"

ChoiceWidget::ChoiceWidget(const Rectangle &r, const int a)
    : ActiveWidget(r, a)
    , m_normalImage(0)
    , m_selectedImage(0)
{}

ChoiceWidget::~ChoiceWidget()
{}

void
ChoiceWidget::setImage(Image *normal, Image *selected)
{
    if ((!normal) || (!selected))
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_normalImage = normal;
    m_selectedImage = selected;
}

void
ChoiceWidget::draw()
{
    if (isVisible())
    {
        if (PreferencesDialogBridge::getInstance()->getSelectState(m_action))
        {
            m_selectedImage->draw(m_rect.getXPos(), m_rect.getYPos(), 0);
        }
        else
        {
            m_normalImage->draw(m_rect.getXPos(), m_rect.getYPos(), 0);
        }
    }
}

void
ChoiceWidget::leftClick(const bool toggle, const int x, const int y)
{
    if (isVisible())
    {
        if (toggle)
        {
            ActionEvent ae(m_action, x, y);
            for (std::list<ActionEventListener *>::iterator it = m_actionListeners.begin(); it != m_actionListeners.end(); ++it)
            {
                (*it)->actionPerformed(ae);
            }
        }
    }
}

void
ChoiceWidget::rightClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        if (toggle)
        {}
    }
}

void
ChoiceWidget::drag(const int, const int)
{}

void
ChoiceWidget::drop(const int, const int)
{}
