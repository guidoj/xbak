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

#ifndef WIDGET_FACTORY_H
#define WIDGET_FACTORY_H

#include "badgewidget.h"
#include "characterbuttonwidget.h"
#include "choicewidget.h"
#include "combatviewwidget.h"
#include "compasswidget.h"
#include "equipmentitemwidget.h"
#include "equipmentwidget.h"
#include "fontresource.h"
#include "imagebuttonwidget.h"
#include "imagewidget.h"
#include "inventoryitemwidget.h"
#include "inventorywidget.h"
#include "labelresource.h"
#include "mapviewwidget.h"
#include "panelwidget.h"
#include "portraitwidget.h"
#include "ratingswidget.h"
#include "requestresource.h"
#include "screenresource.h"
#include "skillswidget.h"
#include "textbuttonwidget.h"
#include "worldviewwidget.h"

class WidgetFactory
{
public:
    WidgetFactory();
    virtual ~WidgetFactory();
    TextButtonWidget* createTextButton ( RequestData& data, FontResource& fnt, ActionEventListener *ael );
    ImageButtonWidget* createImageButton ( RequestData& data, ImageResource& normal, ImageResource& pressed, ActionEventListener *ael );
    CharacterButtonWidget* createCharacterButton ( RequestData& data, PlayerCharacter *pc, ImageResource& img, ActionEventListener *ael );
    ChoiceWidget* createChoice ( RequestData& data, ImageResource& img, ActionEventListener *ael );
    CompassWidget* createCompass ( Camera *cam, Image *img );
    CombatViewWidget* createCombatView ( RequestData& data, Game *game );
    MapViewWidget* createMapView ( RequestData& data, Game *game );
    WorldViewWidget* createWorldView ( RequestData& data, Game *game );
    TextWidget* createLabel ( LabelData& data, FontResource& fnt, const int panelWidth );
    BadgeWidget* createBadge ( const Rectangle &r, const std::string& s, Font *f );
    ImageWidget* createImage ( const Rectangle &r, Image *img, const Flipping flip = NONE );
    InventoryItemWidget* createInventoryItem ( const Rectangle &r, const int a, InventoryItem *item, Image *img, const std::string& s, Font *f, ActionEventListener *ael );
    InventoryWidget *createInventory ( const Rectangle &r, PlayerCharacter *pc, ImageResource& img, FontResource& fnt, ActionEventListener *ael );
    EquipmentItemWidget* createEquipmentItem ( const Rectangle &r, const ObjectType t, InventoryItem *item, Image *img, const std::string& s, Font *f );
    EquipmentWidget *createEquipment ( const Rectangle &r, PlayerCharacter *pc, ImageResource& img, ImageResource& slot, FontResource& fnt );
    PortraitWidget* createPortrait ( const Rectangle &r, PlayerCharacter *pc, Image *hb, Image *vb );
    RatingsWidget* createRatings ( const Rectangle &r, PlayerCharacter *pc, Image *hb, Image *vb, Font *f );
    SkillsWidget* createSkills ( const Rectangle &r, PlayerCharacter *pc, Image *sw, Image *bl, Font *f );
    PanelWidget* createPanel ( const Rectangle &r, Image *img );
};

#endif

