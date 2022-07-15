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

#ifndef PREFERENCES_H
#define PREFERENCES_H

typedef enum _StepTurnSize
{
    STS_SMALL,
    STS_MEDIUM,
    STS_LARGE
} StepTurnSize;

typedef enum _TextSpeed
{
    TS_WAIT,
    TS_MEDIUM,
    TS_FAST
} TextSpeed;

typedef enum _LevelOfDetail
{
    LOD_MIN,
    LOD_LOW,
    LOD_HIGH,
    LOD_MAX
} LevelOfDetail;

class Preferences
{
private:
    StepTurnSize m_stepSize;
    StepTurnSize m_turnSize;
    TextSpeed m_textSpeed;
    LevelOfDetail m_detail;
    bool m_sound;
    bool m_music;
    bool m_combatMusic;
    bool m_cdMusic;
    bool m_introduction;
public:
    Preferences();
    ~Preferences();
    void setDefaults();
    void copy ( const Preferences &prefs );
    StepTurnSize getStepSize() const;
    void setStepSize ( const StepTurnSize sz );
    StepTurnSize getTurnSize() const;
    void setTurnSize ( const StepTurnSize sz );
    TextSpeed getTextSpeed() const;
    void setTextSpeed ( const TextSpeed ts );
    LevelOfDetail getDetail() const;
    void setDetail ( const LevelOfDetail lod );
    bool getSound() const;
    void setSound ( const bool toggle );
    bool getMusic() const;
    void setMusic ( const bool toggle );
    bool getCombatMusic() const;
    void setCombatMusic ( const bool toggle );
    bool getCdMusic() const;
    void setCdMusic ( const bool toggle );
    bool getIntroduction() const;
    void setIntroduction ( const bool toggle );
};

#endif
