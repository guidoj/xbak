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

#ifndef INVENTORY_WIDGET_H
#define INVENTORY_WIDGET_H

#include "containerwidget.h"
#include "font.h"
#include "imageresource.h"
#include "observer.h"
#include "playercharacter.h"

class InventoryWidget
    : public ActionEventListener
    , public ContainerWidget
    , public Observer
{
private:
    PlayerCharacter *m_character;
    ImageResource& m_images;
    Font *m_font;
    std::list<Rectangle> m_freeSpaces;
public:
    InventoryWidget ( const Rectangle &r, PlayerCharacter *pc, ImageResource& img, Font *f );
    virtual ~InventoryWidget();
    void actionPerformed ( const ActionEvent &ae );
    void update();
};

#endif
