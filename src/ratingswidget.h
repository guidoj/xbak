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

#ifndef RATINGS_WIDGET_H
#define RATINGS_WIDGET_H

#include "playercharacter.h"
#include "textwidget.h"

class RatingsWidget
    : public Widget
{
private:
    PlayerCharacter *m_playerCharacter;
    Image *m_horizontalBorder;
    Image *m_verticalBorder;
    TextWidget *m_ratingsLabel;
    TextWidget *m_conditionLabel;
    TextWidget *m_healthLabel;
    TextWidget *m_staminaLabel;
    TextWidget *m_speedLabel;
    TextWidget *m_strengthLabel;
    TextWidget *m_healthOfLabel;
    TextWidget *m_staminaOfLabel;
    TextWidget *m_actualHealth;
    TextWidget *m_actualStamina;
    TextWidget *m_actualSpeed;
    TextWidget *m_actualStrength;
    TextWidget *m_maximumHealth;
    TextWidget *m_maximumStamina;
    TextWidget *m_condition;
public:
    RatingsWidget ( const Rectangle &r, PlayerCharacter *pc, Font *f );
    virtual ~RatingsWidget();
    void setBorders ( Image *hb, Image *vb );
    void draw();
    void drag ( const int x, const int y );
    void drop ( const int x, const int y );
};

#endif
