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

#ifndef CONFIG_RESOURCE_H
#define CONFIG_RESOURCE_H

#include "configdata.h"
#include "preferences.h"

class ConfigResource
    : public ConfigData
{
private:
    Preferences *m_prefs;
public:
    ConfigResource();
    virtual ~ConfigResource();
    Preferences * getPreferences();
    void setPreferences ( Preferences *p );
    void load ( FileBuffer *buffer );
    unsigned int save ( FileBuffer *buffer );
};

#endif
