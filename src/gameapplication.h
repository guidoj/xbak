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

#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "configresource.h"
#include "gameresource.h"
#include "gamestate.h"

class GameApplication
    : public KeyboardEventListener
    , public PointerButtonEventListener
    , public TimerEventListener
{
private:
    friend class GameState;
    bool m_done;
    bool m_inputGrabbed;
    ConfigResource *m_config;
    GameResource *m_game;
    GameState *m_state;
    int m_screenSaveCount;
    static GameApplication *m_instance;
    void setState ( GameState *st );
protected:
    GameApplication();
public:
    ~GameApplication();
    static GameApplication* getInstance();
    static void cleanUp();
    Preferences* getPreferences();
    Game* getGame();
    void playIntro();
    void startNewGame();
    void quitGame();
    void saveConfig();
    void run();
    void keyPressed ( const KeyboardEvent& kbe );
    void keyReleased ( const KeyboardEvent& kbe );
    void pointerButtonPressed ( const PointerButtonEvent& pbe );
    void pointerButtonReleased ( const PointerButtonEvent& pbe );
    void timerExpired ( const TimerEvent& te );
};

#endif
