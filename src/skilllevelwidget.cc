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

#include "skilllevelwidget.h"

SkillLevelWidget::SkillLevelWidget(const Rectangle &r, const Side s, Image *sw, Image *bl, Font *f)
    : Widget(r)
    , m_side(s)
    , m_sword(sw)
    , m_blood(bl)
    , m_skill(0)
    , m_level(0)
    , m_value(0)
{
    if (m_side == LEFT_SIDE)
    {
        m_skill = new TextWidget(Rectangle(m_rect.getXPos() + 34, m_rect.getYPos(), 72, 12), f);
        m_skill->setAlignment(HA_LEFT, VA_TOP);
        m_skill->setColor(TEXT_COLOR_NORMAL);
        m_skill->setShadow(SHADOW_COLOR, 1, 1);
        m_level = new TextWidget(Rectangle(m_rect.getXPos() + 107, m_rect.getYPos(), 20, 12), f);
        m_level->setAlignment(HA_RIGHT, VA_TOP);
        m_level->setColor(TEXT_COLOR_NORMAL);
        m_level->setShadow(SHADOW_COLOR, 1, 1);
    }
    else
    {
        m_skill = new TextWidget(Rectangle(m_rect.getXPos() + 6, m_rect.getYPos(), 72, 12), f);
        m_skill->setAlignment(HA_LEFT, VA_TOP);
        m_skill->setColor(TEXT_COLOR_NORMAL);
        m_skill->setShadow(SHADOW_COLOR, 1, 1);
        m_level = new TextWidget(Rectangle(m_rect.getXPos() + 79, m_rect.getYPos(), 20, 12), f);
        m_level->setAlignment(HA_RIGHT, VA_TOP);
        m_level->setColor(TEXT_COLOR_NORMAL);
        m_level->setShadow(SHADOW_COLOR, 1, 1);
    }
}

SkillLevelWidget::~SkillLevelWidget()
{
    if (m_skill)
    {
        delete m_skill;
    }
    if (m_level)
    {
        delete m_level;
    }
}

void
SkillLevelWidget::setLevel(const std::string& s, const int v)
{
    m_skill->setText(s);
    m_value = v;
    if (m_value > 0)
    {
        std::stringstream stream;
        stream << std::setw(2) << std::setfill(' ') << m_value << '%';
        m_level->setText(stream.str());
    }
    else
    {
        m_level->setText("N/A");
    }
}

void
SkillLevelWidget::draw()
{
    if (isVisible())
    {
        m_skill->draw();
        m_level->draw();
        m_sword->draw(m_rect.getXPos(), m_rect.getYPos() + 2, 0);
        int w = (int)(m_blood->getWidth() * m_value / 100.0f);
        if (m_side == LEFT_SIDE)
        {
            m_blood->draw(m_rect.getXPos() + 31, m_rect.getYPos() + 10, m_blood->getWidth() - w, 0, w, m_blood->getHeight(), 0);
        }
        else
        {
            m_blood->draw(m_rect.getXPos(), m_rect.getYPos() + 10, 0, 0, w, m_blood->getHeight(), 0);
        }
    }
}

void
SkillLevelWidget::drag(const int, const int)
{}

void
SkillLevelWidget::drop(const int, const int)
{}
