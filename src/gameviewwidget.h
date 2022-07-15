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

#ifndef GAME_VIEW_WIDGET_H
#define GAME_VIEW_WIDGET_H

#include "containerwidget.h"
#include "game.h"

class GameViewWidget
    : public ContainerWidget
    , public Observer
{
private:
    virtual void redraw() = 0;
protected:
    Game *m_game;
    Image *m_cachedImage;
public:
    GameViewWidget ( const Rectangle &r, Game *g );
    virtual ~GameViewWidget();
    void draw();
    void update();
};

#endif
