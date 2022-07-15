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

#ifndef DIALOG_FACTORY_H
#define DIALOG_FACTORY_H

#include "dialog.h"
#include "paletteresource.h"
#include "widgetfactory.h"

class DialogFactory
{
private:
    RequestResource m_request;
    PaletteResource m_palette;
    ScreenResource m_screen;
    ImageResource m_normal;
    ImageResource m_pressed;
    ImageResource m_heads;
    ImageResource m_compass;
    ImageResource m_icons;
    ImageResource m_images;
    FontResource m_font;
    LabelResource m_label;
    WidgetFactory m_widgetFactory;
public:
    DialogFactory();
    virtual ~DialogFactory();
    Dialog* createCampDialog();
    Dialog* createCastDialog();
    Dialog* createContentsDialog();
    Dialog* createFullMapDialog();
    Dialog* createInfoDialog();
    Dialog* createInventoryDialog();
    Dialog* createLoadDialog();
    Dialog* createMapDialog();
    Dialog* createOptionsDialog ( const bool firstTime );
    Dialog* createPreferencesDialog();
    Dialog* createSaveDialog();
    Dialog* createWorldDialog();
};

#endif
