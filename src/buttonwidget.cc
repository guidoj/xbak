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

#include "buttonwidget.h"

ButtonWidget::ButtonWidget(const Rectangle &r, const int a)
    : ActiveWidget(r, a)
    , m_enabled(true)
    , m_pressed(false)
{}

ButtonWidget::~ButtonWidget()
{}

void
ButtonWidget::setEnabled(const bool toggle)
{
    m_enabled = toggle;
}

bool
ButtonWidget::isEnabled() const
{
    return m_enabled;
}

void
ButtonWidget::setPressed(const bool toggle)
{
    m_pressed = toggle;
}

bool
ButtonWidget::isPressed() const
{
    return m_pressed;
}

void
ButtonWidget::reset()
{
    m_pressed = false;
}

void
ButtonWidget::drag(const int, const int)
{}

void
ButtonWidget::drop(const int, const int)
{}
