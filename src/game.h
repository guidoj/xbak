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

#ifndef GAME_H
#define GAME_H

#include "chapter.h"
#include "party.h"
#include "partyresource.h"
#include "scene.h"

class Game
{
private:
    std::string m_name;
    Chapter *m_chapter;
    Party *m_party;
    Scene *m_scene;
    Camera *m_camera;
    PartyResource m_partyRes;
    ImageResource m_buttonImages;
public:
    Game();
    ~Game();
    std::string& getName();
    void setName ( const std::string& s );
    Party* getParty() const;
    Chapter* getChapter() const;
    Camera* getCamera() const;
    Scene* getScene() const;
};

#endif

