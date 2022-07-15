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
#include "objectresource.h"
#include "widgetfactory.h"

WidgetFactory::WidgetFactory()
{}

WidgetFactory::~WidgetFactory()
{}

TextButtonWidget*
WidgetFactory::createTextButton(RequestData& data, FontResource &fnt, ActionEventListener *ael)
{
    TextButtonWidget *button = new TextButtonWidget(Rectangle(data.xpos, data.ypos, data.width, data.height), data.action);
    button->setVisible(data.visible);
    button->setLabel(data.label, fnt.getFont());
    button->addActionListener(ael);
    return button;
}

ImageButtonWidget*
WidgetFactory::createImageButton(RequestData& data, ImageResource& normal, ImageResource& pressed, ActionEventListener *ael)
{
    ImageButtonWidget *button = new ImageButtonWidget(Rectangle(data.xpos, data.ypos, data.width, data.height), data.action);
    button->setVisible(data.visible);
    Image *normalImage = 0;
    Image *pressedImage = 0;
    if (data.image >= 0)
    {
        normalImage = normal.getImage(data.image);
        pressedImage = pressed.getImage(data.image);
    }
    button->setImage(normalImage, pressedImage);
    button->addActionListener(ael);
    return button;
}

CharacterButtonWidget*
WidgetFactory::createCharacterButton(RequestData& data, PlayerCharacter *pc, ImageResource& img, ActionEventListener *ael)
{
    CharacterButtonWidget *button = new CharacterButtonWidget(Rectangle(data.xpos, data.ypos, data.width, data.height), data.action);
    button->setCharacter(pc);
    button->setImage(img.getImage(SELECTED_IMAGE));
    button->addActionListener(ael);
    return button;
}

ChoiceWidget*
WidgetFactory::createChoice(RequestData& data, ImageResource& img, ActionEventListener *ael)
{
    ChoiceWidget *choice = new ChoiceWidget(Rectangle(data.xpos, data.ypos, data.width, data.height), data.action);
    choice->setImage(img.getImage(data.image + 1), img.getImage(data.image));
    choice->addActionListener(ael);
    return choice;
}

CompassWidget*
WidgetFactory::createCompass(Camera *cam, Image *img)
{
    CompassWidget *compass = new CompassWidget(cam, img);
    return compass;
}

CombatViewWidget*
WidgetFactory::createCombatView(RequestData& data, Game *game)
{
    return new CombatViewWidget(Rectangle(data.xpos, data.ypos, data.width, data.height), game);
}

MapViewWidget*
WidgetFactory::createMapView(RequestData& data, Game *game)
{
    return new MapViewWidget(Rectangle(data.xpos, data.ypos, data.width, data.height), game);
}

WorldViewWidget*
WidgetFactory::createWorldView(RequestData& data, Game *game)
{
    return new WorldViewWidget(Rectangle(data.xpos, data.ypos, data.width, data.height), game);
}

TextWidget*
WidgetFactory::createLabel(LabelData& data, FontResource& fnt, const int panelWidth)
{
    unsigned int width = 1;
    switch (data.type)
    {
    case LBL_STANDARD:
        for (unsigned int i = 0; i < data.label.length(); i++)
        {
            width += fnt.getFont()->getWidth((unsigned int)data.label[i] - fnt.getFont()->getFirst());
        }
        break;
    case LBL_TITLE:
        width = panelWidth;
        break;
    default:
        break;
    }
    TextWidget *label = new TextWidget(Rectangle(data.xpos, data.ypos, width, fnt.getFont()->getHeight() + 1), fnt.getFont());
    label->setText(data.label);
    label->setColor(data.color);
    if (data.type == LBL_TITLE)
    {
        label->setShadow(data.shadow, 0, 1);
        label->setAlignment(HA_CENTER, VA_TOP);
    }
    return label;
}

BadgeWidget*
WidgetFactory::createBadge(const Rectangle &r, const std::string& s, Font *f)
{
    BadgeWidget *badge = new BadgeWidget(r);
    badge->setLabel(s, f);
    return badge;
}

ImageWidget*
WidgetFactory::createImage(const Rectangle &r, Image *img, const Flipping flip)
{
    ImageWidget *image = new ImageWidget(r, img);
    switch (flip)
    {
    case HORIZONTAL:
        image->horizontalFlip();
        break;
    case VERTICAL:
        image->verticalFlip();
        break;
    default:
        break;
    }
    return image;
}

InventoryItemWidget*
WidgetFactory::createInventoryItem(const Rectangle &r, const int a, InventoryItem *item, Image *img, const std::string& s, Font *f, ActionEventListener *ael)
{
    InventoryItemWidget* invitem = new InventoryItemWidget(r, a);
    invitem->setDraggable(true);
    invitem->setInventoryItem(item);
    invitem->setImage(img);
    invitem->setLabel(s, f);
    invitem->addActionListener(ael);
    return invitem;
}

InventoryWidget *
WidgetFactory::createInventory(const Rectangle &r, PlayerCharacter *pc, ImageResource& img, FontResource& fnt, ActionEventListener *ael)
{
    InventoryWidget *inv = new InventoryWidget(r, pc, img, fnt.getFont());
    inv->setDraggable(true);
    inv->addActionListener(ael);
    return inv;
}

EquipmentItemWidget*
WidgetFactory::createEquipmentItem(const Rectangle &r, const ObjectType t, InventoryItem *item, Image *img, const std::string& s, Font *f)
{
    EquipmentItemWidget* eqitem = new EquipmentItemWidget(r, t);
    eqitem->setInventoryItem(item);
    eqitem->setImage(img);
    eqitem->setLabel(s, f);
    return eqitem;
}

EquipmentWidget *
WidgetFactory::createEquipment(const Rectangle &r, PlayerCharacter *pc, ImageResource& img, ImageResource& slot, FontResource& fnt)
{
    return new EquipmentWidget(r, pc, img, slot.getImage(11), slot.getImage(10), fnt.getFont());
}

PortraitWidget*
WidgetFactory::createPortrait(const Rectangle &r, PlayerCharacter *pc, Image *hb, Image *vb)
{
    PortraitWidget *portrait = new PortraitWidget(r, pc);
    portrait->setBorders(hb, vb);
    return portrait;
}

RatingsWidget*
WidgetFactory::createRatings(const Rectangle &r, PlayerCharacter *pc, Image *hb, Image *vb, Font *f)
{
    RatingsWidget *ratings = new RatingsWidget(r, pc, f);
    ratings->setBorders(hb, vb);
    return ratings;
}

SkillsWidget*
WidgetFactory::createSkills(const Rectangle &r, PlayerCharacter *pc, Image *sw, Image *bl, Font *f)
{
    SkillsWidget *skills = new SkillsWidget(r, pc, sw, bl, f);
    return skills;
}

PanelWidget*
WidgetFactory::createPanel(const Rectangle &r, Image *img)
{
    PanelWidget *panel = new PanelWidget(r);
    panel->setBackground(img);
    return panel;
}
