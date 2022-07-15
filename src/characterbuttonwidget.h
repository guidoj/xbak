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

#ifndef CHARACTER_BUTTON_WIDGET_H
#define CHARACTER_BUTTON_WIDGET_H

#include "buttonwidget.h"
#include "playercharacter.h"

const unsigned int SELECTED_IMAGE = 7;

class CharacterButtonWidget : public ButtonWidget
{
private:
    PlayerCharacter *m_character;
    static Image *m_selectedImage;
public:
    CharacterButtonWidget ( const Rectangle &r, const int a );
    virtual ~CharacterButtonWidget();
    void setCharacter ( PlayerCharacter *pc );
    void setImage ( Image *selected );
    void draw();
    void leftClick ( const bool toggle, const int x, const int y );
    void rightClick ( const bool toggle, const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
