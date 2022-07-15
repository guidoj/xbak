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

#ifndef SKILL_LEVEL_WIDGET_H
#define SKILL_LEVEL_WIDGET_H

#include "image.h"
#include "textwidget.h"

typedef enum _Side
{
    LEFT_SIDE, RIGHT_SIDE
} Side;

class SkillLevelWidget
    : public Widget
{
private:
    Side m_side;
    Image *m_sword;
    Image *m_blood;
    TextWidget *m_skill;
    TextWidget *m_level;
    int m_value;
public:
    SkillLevelWidget ( const Rectangle &r, const Side s, Image *sw, Image *bl, Font *f );
    virtual ~SkillLevelWidget();
    void setLevel ( const std::string& s, const int v );
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
