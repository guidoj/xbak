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

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "dialogfactory.h"

class GameApplication;

class GameState
{
protected:
    GameApplication *m_gameApp;
    DialogFactory m_dialogFactory;
    GameState *m_prevState;
    void changeState ( GameState *state, const bool savePreviousState = false );
public:
    GameState();
    virtual ~GameState();
    virtual void enter() = 0;
    virtual void leave() = 0;
    virtual void execute() = 0;
    virtual void move();
    virtual void turn();
};

class GameStateCamp
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateCamp *m_instance;
protected:
    GameStateCamp();
public:
    ~GameStateCamp();
    static GameStateCamp* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateCast
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateCast *m_instance;
protected:
    GameStateCast();
public:
    ~GameStateCast();
    static GameStateCast* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateChapter
    : public GameState
{
private:
    static GameStateChapter *m_instance;
protected:
    GameStateChapter();
public:
    ~GameStateChapter();
    static GameStateChapter* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateCombat
    : public GameState
{
private:
    static GameStateCombat *m_instance;
protected:
    GameStateCombat();
public:
    ~GameStateCombat();
    static GameStateCombat* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateContents
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateContents *m_instance;
protected:
    GameStateContents();
public:
    ~GameStateContents();
    static GameStateContents* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateFullMap
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateFullMap *m_instance;
protected:
    GameStateFullMap();
public:
    ~GameStateFullMap();
    static GameStateFullMap* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateInitialOptions
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateInitialOptions *m_instance;
protected:
    GameStateInitialOptions();
public:
    ~GameStateInitialOptions();
    static GameStateInitialOptions* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateIntro
    : public GameState
{
private:
    static GameStateIntro *m_instance;
protected:
    GameStateIntro();
public:
    ~GameStateIntro();
    static GameStateIntro* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateInventory
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateInventory *m_instance;
protected:
    GameStateInventory();
public:
    ~GameStateInventory();
    static GameStateInventory* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateLoad
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateLoad *m_instance;
protected:
    GameStateLoad();
public:
    ~GameStateLoad();
    static GameStateLoad* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateMap
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateMap *m_instance;
protected:
    GameStateMap();
public:
    ~GameStateMap();
    static GameStateMap* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateOptions
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateOptions *m_instance;
protected:
    GameStateOptions();
public:
    ~GameStateOptions();
    static GameStateOptions* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStatePreferences
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStatePreferences *m_instance;
protected:
    GameStatePreferences();
public:
    ~GameStatePreferences();
    static GameStatePreferences* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateInfo
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateInfo *m_instance;
protected:
    GameStateInfo();
public:
    ~GameStateInfo();
    static GameStateInfo* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateSave
    : public GameState
{
private:
    Dialog *m_dialog;
    static GameStateSave *m_instance;
protected:
    GameStateSave();
public:
    ~GameStateSave();
    static GameStateSave* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
};

class GameStateWorld
    : public GameState
{
private:
    Dialog *m_dialog;
    int m_moving;
    int m_turning;
    static GameStateWorld *m_instance;
protected:
    GameStateWorld();
public:
    ~GameStateWorld();
    static GameStateWorld* getInstance();
    static void cleanUp();
    void enter();
    void leave();
    void execute();
    void move();
    void turn();
};

#endif
