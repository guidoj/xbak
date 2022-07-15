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

#ifndef PREFERENCES_DIALOG_BRIDGE_H
#define PREFERENCES_DIALOG_BRIDGE_H

#include "preferences.h"

class PreferencesDialogBridge
{
private:
    Preferences m_prefs;
    static PreferencesDialogBridge* m_instance;
protected:
    PreferencesDialogBridge();
public:
    ~PreferencesDialogBridge();
    static PreferencesDialogBridge* getInstance();
    static void cleanUp();
    void fetch();
    void commit();
    bool getSelectState ( const unsigned int action );
    void setSelectState ( const unsigned int action );
    void setDefaults();
};

#endif
