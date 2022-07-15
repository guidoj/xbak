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

#include <iomanip>
#include <sstream>

#include "defines.h"
#include "dialogfactory.h"
#include "exception.h"
#include "filemanager.h"
#include "gameapplication.h"

DialogFactory::DialogFactory()
{}

DialogFactory::~DialogFactory()
{}

Dialog *
DialogFactory::createCampDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_CAMP.DAT");
        FileManager::getInstance()->load(&m_palette, "OPTIONS.PAL");
        FileManager::getInstance()->load(&m_screen, "ENCAMP.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_pressed, "BICONS2.BMX");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new GameDialog(m_palette.getPalette(), new DialogWindow(panel));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_IMAGEBUTTON:
                data.xpos += m_request.getXOff();
                data.ypos += m_request.getYOff();
                panel->addActiveWidget(m_widgetFactory.createImageButton(data, m_normal, m_pressed, dialog));
                break;
            default:
                break;
            }
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::CreateCampDialog");
        throw;
    }
}

Dialog *
DialogFactory::createCastDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_CAST.DAT");
        FileManager::getInstance()->load(&m_palette, "OPTIONS.PAL");
        FileManager::getInstance()->load(&m_screen, "FRAME.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_pressed, "BICONS2.BMX");
        FileManager::getInstance()->load(&m_heads, "HEADS.BMX");
        FileManager::getInstance()->load(&m_compass, "COMPASS.BMX");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new GameDialog(m_palette.getPalette(), new DialogWindow(panel));
        unsigned int nextMember = 0;
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_USERDEFINED:
                if ((data.action >= 0) && (data.group == GROUP2))
                {
                    panel->addActiveWidget(m_widgetFactory.createCharacterButton(data, GameApplication::getInstance()->getGame()->getParty()->getActiveMember(nextMember), m_heads, dialog));
                    nextMember++;
                }
                break;
            case REQ_IMAGEBUTTON:
                data.xpos += m_request.getXOff();
                data.ypos += m_request.getYOff();
                panel->addActiveWidget(m_widgetFactory.createImageButton(data, m_normal, m_pressed, dialog));
                break;
            default:
                break;
            }
        }
        panel->addWidget(m_widgetFactory.createCompass(GameApplication::getInstance()->getGame()->getCamera(), m_compass.getImage(0)));
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::createCastDialog");
        throw;
    }
}

Dialog *
DialogFactory::createContentsDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "CONTENTS.DAT");
        FileManager::getInstance()->load(&m_palette, "CONTENTS.PAL");
        FileManager::getInstance()->load(&m_screen, "CONT2.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_pressed, "BICONS2.BMX");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new OptionsDialog(m_palette.getPalette(), new DialogWindow(panel));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_IMAGEBUTTON:
                data.xpos += m_request.getXOff();
                data.ypos += m_request.getYOff();
                panel->addActiveWidget(m_widgetFactory.createImageButton(data, m_normal, m_pressed, dialog));
                break;
            default:
                break;
            }
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::createContentsDialog");
        throw;
    }
}

Dialog *
DialogFactory::createFullMapDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_FMAP.DAT");
        FileManager::getInstance()->load(&m_palette, "FULLMAP.PAL");
        FileManager::getInstance()->load(&m_screen, "FULLMAP.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_pressed, "BICONS2.BMX");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new GameDialog(m_palette.getPalette(), new DialogWindow(panel));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_IMAGEBUTTON:
                data.xpos += m_request.getXOff();
                data.ypos += m_request.getYOff();
                panel->addActiveWidget(m_widgetFactory.createImageButton(data, m_normal, m_pressed, dialog));
                break;
            default:
                break;
            }
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::CreateFullMapDialog");
        throw;
    }
}

Dialog *
DialogFactory::createInfoDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_INFO.DAT");
        FileManager::getInstance()->load(&m_palette, "INVENTOR.PAL");
        FileManager::getInstance()->load(&m_screen, "DIALOG.SCX");
        FileManager::getInstance()->load(&m_icons, "INVSHP1.BMX");
        FileManager::getInstance()->load(&m_images, "INVSHP2.BMX");
        FileManager::getInstance()->load(&m_font, "GAME.FNT");

        PlayerCharacter *pc = GameApplication::getInstance()->getGame()->getParty()->getSelectedMember();
        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new GameDialog(m_palette.getPalette(), new DialogWindow(panel));
        panel->addWidget(m_widgetFactory.createImage(Rectangle(2, 107, 122, 91), m_images.getImage(24)));
        panel->addWidget(m_widgetFactory.createImage(Rectangle(188, 107, 122, 91), m_images.getImage(24), HORIZONTAL));
        panel->addWidget(m_widgetFactory.createPortrait(Rectangle(7, 9, 71, 71), pc, m_images.getImage(26), m_images.getImage(25)));
        panel->addWidget(m_widgetFactory.createBadge(Rectangle(23, 71, 42, 12), pc->getName(), m_font.getFont()));
        panel->addWidget(m_widgetFactory.createRatings(Rectangle(84, 9, 222, 71), pc, m_images.getImage(26), m_images.getImage(25), m_font.getFont()));
        panel->addWidget(m_widgetFactory.createSkills(Rectangle(16, 86, 276, 105), pc, m_images.getImage(21), m_images.getImage(22), m_font.getFont()));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_TEXTBUTTON:
                panel->addActiveWidget(m_widgetFactory.createTextButton(data, m_font, dialog));
                break;
            default:
                break;
            }
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::createInfoDialog");
        throw;
    }
}

Dialog *
DialogFactory::createInventoryDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_INV.DAT");
        FileManager::getInstance()->load(&m_palette, "INVENTOR.PAL");
        FileManager::getInstance()->load(&m_screen, "INVENTOR.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_pressed, "BICONS2.BMX");
        FileManager::getInstance()->load(&m_icons, "INVSHP1.BMX");
        FileManager::getInstance()->load(&m_images, "INVSHP2.BMX");
        FileManager::getInstance()->load(&m_heads, "HEADS.BMX");
        FileManager::getInstance()->load(&m_font, "GAME.FNT");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new GameDialog(m_palette.getPalette(), new DialogWindow(panel));
        unsigned int nextMember = 0;
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_USERDEFINED:
                if ((data.action >= 0) && (data.group == GROUP3))
                {
                    PlayerCharacter *pc = GameApplication::getInstance()->getGame()->getParty()->getActiveMember(nextMember);
                    panel->addActiveWidget(m_widgetFactory.createCharacterButton(data, pc, m_heads, dialog));
                    panel->addActiveWidget(m_widgetFactory.createEquipment(Rectangle(13, 11, 82, 121), pc, m_icons, m_images, m_font));
                    panel->addActiveWidget(m_widgetFactory.createInventory(Rectangle(105, 11, 202, 121), pc, m_icons, m_font, dialog));
                    nextMember++;
                }
                break;
            case REQ_IMAGEBUTTON:
                data.xpos += m_request.getXOff();
                data.ypos += m_request.getYOff();
                panel->addActiveWidget(m_widgetFactory.createImageButton(data, m_normal, m_pressed, dialog));
                break;
            case REQ_TEXTBUTTON:
                data.visible = false;
                panel->addActiveWidget(m_widgetFactory.createTextButton(data, m_font, dialog));
                break;
            default:
                break;
            }
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::createInventoryDialog");
        throw;
    }
}

Dialog *
DialogFactory::createLoadDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_LOAD.DAT");
        FileManager::getInstance()->load(&m_palette, "OPTIONS.PAL");
        FileManager::getInstance()->load(&m_screen, "OPTIONS2.SCX");
        FileManager::getInstance()->load(&m_font, "GAME.FNT");
        FileManager::getInstance()->load(&m_label, "LBL_LOAD.DAT");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new OptionsDialog(m_palette.getPalette(), new DialogWindow(panel));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_TEXTBUTTON:
                panel->addActiveWidget(m_widgetFactory.createTextButton(data, m_font, dialog));
                break;
            default:
                break;
            }
        }
        for (unsigned int i = 0; i < m_label.getSize(); i++)
        {
            LabelData data = m_label.getLabelData(i);
            panel->addWidget(m_widgetFactory.createLabel(data, m_font, MAX(m_request.getRectangle().getWidth(), m_screen.getImage()->getWidth())));
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::createLoadDialog");
        throw;
    }
}

Dialog *
DialogFactory::createMapDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_MAP.DAT");
        FileManager::getInstance()->load(&m_palette, "OPTIONS.PAL");
        FileManager::getInstance()->load(&m_screen, "FRAME.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_pressed, "BICONS2.BMX");
        FileManager::getInstance()->load(&m_heads, "HEADS.BMX");
        FileManager::getInstance()->load(&m_compass, "COMPASS.BMX");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new GameDialog(m_palette.getPalette(), new DialogWindow(panel));
        unsigned int nextMember = 0;
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_USERDEFINED:
                if ((data.action >= 0) && (data.group == GROUP2))
                {
                    panel->addActiveWidget(m_widgetFactory.createCharacterButton(data, GameApplication::getInstance()->getGame()->getParty()->getActiveMember(nextMember), m_heads, dialog));
                    nextMember++;
                }
                if ((data.action >= 0) && (data.group == GROUP3))
                {
                    panel->addWidget(m_widgetFactory.createMapView(data, GameApplication::getInstance()->getGame()));
                }
                break;
            case REQ_IMAGEBUTTON:
                data.xpos += m_request.getXOff();
                data.ypos += m_request.getYOff();
                panel->addActiveWidget(m_widgetFactory.createImageButton(data, m_normal, m_pressed, dialog));
                break;
            default:
                break;
            }
        }
        panel->addWidget(m_widgetFactory.createCompass(GameApplication::getInstance()->getGame()->getCamera(), m_compass.getImage(0)));
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::CreateMapDialog");
        throw;
    }
}

Dialog *
DialogFactory::createOptionsDialog(const bool firstTime)
{
    try
    {
        FileManager::getInstance()->load(&m_request, firstTime ? "REQ_OPT0.DAT" : "REQ_OPT1.DAT");
        FileManager::getInstance()->load(&m_palette, "OPTIONS.PAL");
        FileManager::getInstance()->load(&m_screen, firstTime ? "OPTIONS0.SCX" : "OPTIONS1.SCX");
        FileManager::getInstance()->load(&m_font, "GAME.FNT");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new OptionsDialog(m_palette.getPalette(), new DialogWindow(panel));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_TEXTBUTTON:
                panel->addActiveWidget(m_widgetFactory.createTextButton(data, m_font, dialog));
                break;
            default:
                break;
            }
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::CreateOptionsDialog");
        throw;
    }
}

Dialog *
DialogFactory::createPreferencesDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_PREF.DAT");
        FileManager::getInstance()->load(&m_palette, "OPTIONS.PAL");
        FileManager::getInstance()->load(&m_screen, "OPTIONS2.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_font, "GAME.FNT");
        FileManager::getInstance()->load(&m_label, "LBL_PREF.DAT");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new OptionsDialog(m_palette.getPalette(), new DialogWindow(panel));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_TEXTBUTTON:
                panel->addActiveWidget(m_widgetFactory.createTextButton(data, m_font, dialog));
                break;
            case REQ_SELECT:
                panel->addActiveWidget(m_widgetFactory.createChoice(data, m_normal, dialog));
                break;
            default:
                break;
            }
        }
        for (unsigned int i = 0; i < m_label.getSize(); i++)
        {
            LabelData data = m_label.getLabelData(i);
            panel->addWidget(m_widgetFactory.createLabel(data, m_font, MAX(m_request.getRectangle().getWidth(), m_screen.getImage()->getWidth())));
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::createPreferencesDialog");
        throw;
    }
}

Dialog *
DialogFactory::createSaveDialog()
{
    try
    {
        FileManager::getInstance()->load(&m_request, "REQ_SAVE.DAT");
        FileManager::getInstance()->load(&m_palette, "OPTIONS.PAL");
        FileManager::getInstance()->load(&m_screen, "OPTIONS2.SCX");
        FileManager::getInstance()->load(&m_font, "GAME.FNT");
        FileManager::getInstance()->load(&m_label, "LBL_SAVE.DAT");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new OptionsDialog(m_palette.getPalette(), new DialogWindow(panel));
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_TEXTBUTTON:
                panel->addActiveWidget(m_widgetFactory.createTextButton(data, m_font, dialog));
                break;
            default:
                break;
            }
        }
        for (unsigned int i = 0; i < m_label.getSize(); i++)
        {
            LabelData data = m_label.getLabelData(i);
            panel->addWidget(m_widgetFactory.createLabel(data, m_font, MAX(m_request.getRectangle().getWidth(), m_screen.getImage()->getWidth())));
        }
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::CreateSaveDialog");
        throw;
    }
}

Dialog *
DialogFactory::createWorldDialog()
{
    try
    {
        std::stringstream name;
        name << "Z" << std::setw(2) << std::setfill('0') << GameApplication::getInstance()->getGame()->getChapter()->get() << ".PAL";
        FileManager::getInstance()->load(&m_request, "REQ_MAIN.DAT");
        FileManager::getInstance()->load(&m_palette, name.str());
        FileManager::getInstance()->load(&m_screen, "FRAME.SCX");
        FileManager::getInstance()->load(&m_normal, "BICONS1.BMX");
        FileManager::getInstance()->load(&m_pressed, "BICONS2.BMX");
        FileManager::getInstance()->load(&m_heads, "HEADS.BMX");
        FileManager::getInstance()->load(&m_compass, "COMPASS.BMX");

        PanelWidget *panel = m_widgetFactory.createPanel(m_request.getRectangle(), m_screen.getImage());
        Dialog *dialog = new GameDialog(m_palette.getPalette(), new DialogWindow(panel));
        unsigned int nextMember = 0;
        for (unsigned int i = 0; i < m_request.getSize(); i++)
        {
            RequestData data = m_request.getRequestData(i);
            switch (data.widget)
            {
            case REQ_USERDEFINED:
                if ((data.action >= 0) && (data.group == GROUP2))
                {
                    panel->addActiveWidget(m_widgetFactory.createCharacterButton(data, GameApplication::getInstance()->getGame()->getParty()->getActiveMember(nextMember), m_heads, dialog));
                    nextMember++;
                }
                if ((data.action >= 0) && (data.group == GROUP3))
                {
                    panel->addWidget(m_widgetFactory.createWorldView(data, GameApplication::getInstance()->getGame()));
                }
                break;
            case REQ_IMAGEBUTTON:
                data.xpos += m_request.getXOff();
                data.ypos += m_request.getYOff();
                panel->addActiveWidget(m_widgetFactory.createImageButton(data, m_normal, m_pressed, dialog));
                break;
            default:
                break;
            }
        }
        panel->addWidget(m_widgetFactory.createCompass(GameApplication::getInstance()->getGame()->getCamera(), m_compass.getImage(0)));
        return dialog;
    }
    catch (Exception &e)
    {
        e.print("DialogFactory::createWorldDialog");
        throw;
    }
}
