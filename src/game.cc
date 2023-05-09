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
#include "filemanager.h"
#include "game.h"
#include "scenefactory.h"

Game::Game()
    : m_name("")
    , m_chapter(0)
    , m_party(0)
    , m_scene(0)
    , m_camera(0)
{
    try
    {
        FileManager::getInstance()->load(&m_partyRes, "PARTY.DAT");
        FileManager::getInstance()->load(&m_buttonImages, "HEADS.BMX");
        m_chapter = new Chapter(1);
        m_party = new Party;
        for (unsigned int i = 0; i < m_partyRes.getSize(); i++)
        {
            PartyData *pd = m_partyRes.getData(i);
            PlayerCharacter *pc = new PlayerCharacter(pd->name);
            pc->setButtonImage(m_buttonImages.getImage(i));
            m_party->addMember(pc);
        }
        SceneFactory sf(m_chapter->getZone());
        m_scene = sf.createScene();
        m_camera = new Camera(Vector2D(0, 0), 0);
    }
    catch (Exception &e)
    {
        e.print("Game::Game");
        throw;
    }
}

Game::~Game()
{
    if (m_camera)
    {
        delete m_camera;
    }
    if (m_scene)
    {
        delete m_scene;
    }
    if (m_party)
    {
        delete m_party;
    }
    if (m_chapter)
    {
        delete m_chapter;
    }
}

std::string&
Game::getName()
{
    return m_name;
}

void
Game::setName(const std::string& s)
{
    m_name = s;
}

Party *
Game::getParty() const
{
    return m_party;
}

Chapter *
Game::getChapter() const
{
    return m_chapter;
}

Camera *
Game::getCamera() const
{
    return m_camera;
}

Scene *
Game::getScene() const
{
    return m_scene;
}
