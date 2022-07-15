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

#ifndef EQUIPMENT_WIDGET_H
#define EQUIPMENT_WIDGET_H

#include "containerwidget.h"
#include "font.h"
#include "imageresource.h"
#include "observer.h"
#include "playercharacter.h"

class EquipmentWidget
    : public ContainerWidget
    , public Observer
{
private:
    PlayerCharacter *m_character;
    ImageResource& m_images;
    Image *m_armorSlot;
    Image *m_crossbowSlot;
    Font *m_font;
public:
    EquipmentWidget ( const Rectangle &r, PlayerCharacter *pc, ImageResource& img, Image *as, Image *cbs, Font *f );
    virtual ~EquipmentWidget();
    void update();
};

#endif
