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

#include "hotspotwidget.h"
#include "requestresource.h"

HotspotWidget::HotspotWidget(const Rectangle &r, const int a)
    : ActiveWidget(r, a)
{
    setFocusable(false);
}

HotspotWidget::~HotspotWidget()
{
}

void
HotspotWidget::leftClick(const bool toggle, const int x, const int y )
{
    if ( x > 0 )
    {
    }
    if ( y > 0 )
    {
    }
    generateActionEvent(toggle ? getAction() : ACT_STOP);
}

void
HotspotWidget::rightClick(const bool toggle, const int x, const int y )
{
    if (toggle)
    {
        if ( x > 0 )
        {
        }
        if ( y > 0 )
        {
        }
    }
}
