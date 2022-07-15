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

#include "characterbuttonwidget.h"
#include "exception.h"
#include "gameapplication.h"
#include "pointermanager.h"

Image* CharacterButtonWidget::m_selectedImage = 0;

CharacterButtonWidget::CharacterButtonWidget(const Rectangle &r, const int a)
    : ButtonWidget(r, a)
    , m_character(0)
{}

CharacterButtonWidget::~CharacterButtonWidget()
{}

void
CharacterButtonWidget::setCharacter(PlayerCharacter *pc)
{
    if (!pc)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_character = pc;
}

void
CharacterButtonWidget::setImage(Image *selected)
{
    if (!selected)
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_selectedImage = selected;
}

void
CharacterButtonWidget::draw()
{
    if (isVisible())
    {
        if (m_character)
        {
            m_character->getButtonImage()->draw(m_rect.getXPos(), m_rect.getYPos(), 0);
            if (m_character->isSelected())
            {
                m_selectedImage->draw(m_rect.getXPos(), m_rect.getYPos(), 0);
            }
        }
    }
}

void
CharacterButtonWidget::leftClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        generateActionEvent(toggle ? getAction() : ACT_STOP);
    }
}

void
CharacterButtonWidget::rightClick(const bool toggle, const int, const int)
{
    if (isVisible())
    {
        generateActionEvent(toggle ? (getAction() + RIGHT_CLICK_OFFSET) : ACT_STOP);
    }
}

void
CharacterButtonWidget::drop(const int, const int)
{
    InventoryItemWidget *widget = PointerManager::getInstance()->getDraggedWidget();
    if (widget)
    {
        InventoryItem *item = widget->getInventoryItem();
        if (item)
        {
            GameApplication::getInstance()->getGame()->getParty()->getSelectedMember()->getInventory()->remove(item);
            m_character->getInventory()->add(item);
        }
    }
}
