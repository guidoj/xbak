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

#include "exception.h"
#include "mediatoolkit.h"
#include "ratingswidget.h"

RatingsWidget::RatingsWidget(const Rectangle &r, PlayerCharacter *pc, Font *f)
    : Widget(r)
    , m_playerCharacter(pc)
    , m_horizontalBorder(0)
    , m_verticalBorder(0)
    , m_ratingsLabel(0)
    , m_conditionLabel(0)
    , m_healthLabel(0)
    , m_staminaLabel(0)
    , m_speedLabel(0)
    , m_strengthLabel(0)
    , m_healthOfLabel(0)
    , m_staminaOfLabel(0)
    , m_actualHealth(0)
    , m_actualStamina(0)
    , m_actualSpeed(0)
    , m_actualStrength(0)
    , m_maximumHealth(0)
    , m_maximumStamina(0)
    , m_condition(0)
{
    m_ratingsLabel = new TextWidget(Rectangle(m_rect.getXPos() + 11, m_rect.getYPos() + 5, 40, 11), f);
    m_ratingsLabel->setText("Ratings:");
    m_ratingsLabel->setAlignment(HA_LEFT, VA_TOP);
    m_ratingsLabel->setColor(INFO_TEXT_COLOR);
    m_ratingsLabel->setShadow(COLOR_BLACK, 1, 1);
    m_conditionLabel = new TextWidget(Rectangle(m_rect.getXPos() + 126, m_rect.getYPos() + 5, 50, 11), f);
    m_conditionLabel->setText("Condition:");
    m_conditionLabel->setAlignment(HA_LEFT, VA_TOP);
    m_conditionLabel->setColor(INFO_TEXT_COLOR);
    m_conditionLabel->setShadow(COLOR_BLACK, 1, 1);
    m_healthLabel = new TextWidget(Rectangle(m_rect.getXPos() + 21, m_rect.getYPos() + 19, 40, 11), f);
    m_healthLabel->setText("Health");
    m_healthLabel->setAlignment(HA_LEFT, VA_TOP);
    m_healthLabel->setColor(INFO_TEXT_COLOR);
    m_healthLabel->setShadow(COLOR_BLACK, 1, 1);
    m_staminaLabel = new TextWidget(Rectangle(m_rect.getXPos() + 21, m_rect.getYPos() + 30, 40, 11), f);
    m_staminaLabel->setText("Stamina");
    m_staminaLabel->setAlignment(HA_LEFT, VA_TOP);
    m_staminaLabel->setColor(INFO_TEXT_COLOR);
    m_staminaLabel->setShadow(COLOR_BLACK, 1, 1);
    m_speedLabel = new TextWidget(Rectangle(m_rect.getXPos() + 21, m_rect.getYPos() + 41, 40, 11), f);
    m_speedLabel->setText("Speed");
    m_speedLabel->setAlignment(HA_LEFT, VA_TOP);
    m_speedLabel->setColor(INFO_TEXT_COLOR);
    m_speedLabel->setShadow(COLOR_BLACK, 1, 1);
    m_strengthLabel = new TextWidget(Rectangle(m_rect.getXPos() + 21, m_rect.getYPos() + 52, 40, 11), f);
    m_strengthLabel->setText("Strength");
    m_strengthLabel->setAlignment(HA_LEFT, VA_TOP);
    m_strengthLabel->setColor(INFO_TEXT_COLOR);
    m_strengthLabel->setShadow(COLOR_BLACK, 1, 1);
    m_healthOfLabel = new TextWidget(Rectangle(m_rect.getXPos() + 86, m_rect.getYPos() + 19, 12, 11), f);
    m_healthOfLabel->setText("of");
    m_healthOfLabel->setAlignment(HA_LEFT, VA_TOP);
    m_healthOfLabel->setColor(INFO_TEXT_COLOR);
    m_healthOfLabel->setShadow(COLOR_BLACK, 1, 1);
    m_staminaOfLabel = new TextWidget(Rectangle(m_rect.getXPos() + 86, m_rect.getYPos() + 30, 12, 11), f);
    m_staminaOfLabel->setText("of");
    m_staminaOfLabel->setAlignment(HA_LEFT, VA_TOP);
    m_staminaOfLabel->setColor(INFO_TEXT_COLOR);
    m_staminaOfLabel->setShadow(COLOR_BLACK, 1, 1);

    std::stringstream actualHealthStream;
    actualHealthStream << std::setw(2) << std::setfill(' ') << m_playerCharacter->getStatistics().get(STAT_HEALTH, STAT_ACTUAL);
    m_actualHealth = new TextWidget(Rectangle(m_rect.getXPos() + 68, m_rect.getYPos() + 19, 12, 11), f);
    m_actualHealth->setText(actualHealthStream.str());
    m_actualHealth->setAlignment(HA_RIGHT, VA_TOP);
    m_actualHealth->setColor(INFO_TEXT_COLOR);
    m_actualHealth->setShadow(COLOR_BLACK, 1, 1);
    std::stringstream actualStaminaStream;
    actualStaminaStream << std::setw(2) << std::setfill(' ') << m_playerCharacter->getStatistics().get(STAT_STAMINA, STAT_ACTUAL);
    m_actualStamina = new TextWidget(Rectangle(m_rect.getXPos() + 68, m_rect.getYPos() + 30, 12, 11), f);
    m_actualStamina->setText(actualStaminaStream.str());
    m_actualStamina->setAlignment(HA_RIGHT, VA_TOP);
    m_actualStamina->setColor(INFO_TEXT_COLOR);
    m_actualStamina->setShadow(COLOR_BLACK, 1, 1);
    std::stringstream actualSpeedStream;
    actualSpeedStream << std::setw(2) << std::setfill(' ') << m_playerCharacter->getStatistics().get(STAT_SPEED, STAT_ACTUAL);
    m_actualSpeed = new TextWidget(Rectangle(m_rect.getXPos() + 68, m_rect.getYPos() + 41, 12, 11), f);
    m_actualSpeed->setText(actualSpeedStream.str());
    m_actualSpeed->setAlignment(HA_RIGHT, VA_TOP);
    m_actualSpeed->setColor(INFO_TEXT_COLOR);
    m_actualSpeed->setShadow(COLOR_BLACK, 1, 1);
    std::stringstream actualStrengthStream;
    actualStrengthStream << std::setw(2) << std::setfill(' ') << m_playerCharacter->getStatistics().get(STAT_STRENGTH, STAT_ACTUAL);
    m_actualStrength = new TextWidget(Rectangle(m_rect.getXPos() + 68, m_rect.getYPos() + 52, 12, 11), f);
    m_actualStrength->setText(actualStrengthStream.str());
    m_actualStrength->setAlignment(HA_RIGHT, VA_TOP);
    m_actualStrength->setColor(INFO_TEXT_COLOR);
    m_actualStrength->setShadow(COLOR_BLACK, 1, 1);
    std::stringstream maximumHealthStream;
    maximumHealthStream << std::setw(2) << std::setfill(' ') << m_playerCharacter->getStatistics().get(STAT_HEALTH, STAT_MAXIMUM);
    m_maximumHealth = new TextWidget(Rectangle(m_rect.getXPos() + 98, m_rect.getYPos() + 19, 12, 11), f);
    m_maximumHealth->setText(maximumHealthStream.str());
    m_maximumHealth->setAlignment(HA_RIGHT, VA_TOP);
    m_maximumHealth->setColor(INFO_TEXT_COLOR);
    m_maximumHealth->setShadow(COLOR_BLACK, 1, 1);
    std::stringstream maximumStaminaStream;
    maximumStaminaStream << std::setw(2) << std::setfill(' ') << m_playerCharacter->getStatistics().get(STAT_STAMINA, STAT_MAXIMUM);
    m_maximumStamina = new TextWidget(Rectangle(m_rect.getXPos() + 98, m_rect.getYPos() + 30, 12, 11), f);
    m_maximumStamina->setText(maximumStaminaStream.str());
    m_maximumStamina->setAlignment(HA_RIGHT, VA_TOP);
    m_maximumStamina->setColor(INFO_TEXT_COLOR);
    m_maximumStamina->setShadow(COLOR_BLACK, 1, 1);
    m_condition = new TextWidget(Rectangle(m_rect.getXPos() + 136, m_rect.getYPos() + 19, 60, 11), f);
    switch (m_playerCharacter->setCondition())
    {
    case COND_NORMAL:
        m_condition->setText("Normal");
        break;
    case COND_SICK:
        m_condition->setText("Sick");
        break;
    case COND_PLAGUED:
        m_condition->setText("Plagued");
        break;
    case COND_POISONED:
        m_condition->setText("Poisoned");
        break;
    case COND_DRUNK:
        m_condition->setText("Drunk");
        break;
    case COND_HEALING:
        m_condition->setText("Healing");
        break;
    case COND_STARVING:
        m_condition->setText("Starving");
        break;
    case COND_NEAR_DEATH:
        m_condition->setText("Near-death");
        break;
    default:
        m_condition->setText("");
        break;
    }
    m_condition->setAlignment(HA_LEFT, VA_TOP);
    m_condition->setColor(INFO_TEXT_COLOR);
    m_condition->setShadow(COLOR_BLACK, 1, 1);
}

RatingsWidget::~RatingsWidget()
{
    if (m_ratingsLabel)
    {
        delete m_ratingsLabel;
    }
    if (m_conditionLabel)
    {
        delete m_conditionLabel;
    }
    if (m_healthLabel)
    {
        delete m_healthLabel;
    }
    if (m_staminaLabel)
    {
        delete m_staminaLabel;
    }
    if (m_speedLabel)
    {
        delete m_speedLabel;
    }
    if (m_strengthLabel)
    {
        delete m_strengthLabel;
    }
    if (m_healthOfLabel)
    {
        delete m_healthOfLabel;
    }
    if (m_staminaOfLabel)
    {
        delete m_staminaOfLabel;
    }
    if (m_actualHealth)
    {
        delete m_actualHealth;
    }
    if (m_actualStamina)
    {
        delete m_actualStamina;
    }
    if (m_actualSpeed)
    {
        delete m_actualSpeed;
    }
    if (m_actualStrength)
    {
        delete m_actualStrength;
    }
    if (m_maximumHealth)
    {
        delete m_maximumHealth;
    }
    if (m_maximumStamina)
    {
        delete m_maximumStamina;
    }
    if (m_condition)
    {
        delete m_condition;
    }
}

void
RatingsWidget::setBorders(Image *hb, Image *vb)
{
    if ((!hb) || (!vb))
    {
        throw NullPointer(__FILE__, __LINE__);
    }
    m_horizontalBorder = hb;
    m_verticalBorder = vb;
}

void
RatingsWidget::draw()
{
    if (isVisible())
    {
        int xoff = 0;
        int yoff = 0;
        if (m_horizontalBorder && m_verticalBorder)
        {
            m_horizontalBorder->draw(m_rect.getXPos() + m_verticalBorder->getWidth(), m_rect.getYPos(), 0, 0,
                                   m_rect.getWidth() - 2 * m_verticalBorder->getWidth(), m_horizontalBorder->getHeight());
            m_horizontalBorder->draw(m_rect.getXPos() + m_verticalBorder->getWidth(), m_rect.getYPos() + m_rect.getHeight() - m_horizontalBorder->getHeight(), 0, 0,
                                   m_rect.getWidth() - 2 * m_verticalBorder->getWidth(), m_horizontalBorder->getHeight());
            m_verticalBorder->draw(m_rect.getXPos(), m_rect.getYPos(), 0, 0,
                                 m_verticalBorder->getWidth(), m_rect.getHeight());
            m_verticalBorder->draw(m_rect.getXPos() + m_rect.getWidth() - m_verticalBorder->getWidth(), m_rect.getYPos(), 0, 0,
                                 m_verticalBorder->getWidth(), m_rect.getHeight());
            xoff = m_verticalBorder->getWidth();
            yoff = m_horizontalBorder->getHeight();
        }
        Video *video = MediaToolkit::getInstance()->getVideo();
        video->fillRect(m_rect.getXPos() + xoff, m_rect.getYPos() + yoff, m_rect.getWidth() - 2 * xoff, m_rect.getHeight() - 2 * yoff, 168);
        m_ratingsLabel->draw();
        m_conditionLabel->draw();
        m_healthLabel->draw();
        m_staminaLabel->draw();
        m_speedLabel->draw();
        m_strengthLabel->draw();
        m_healthOfLabel->draw();
        m_staminaOfLabel->draw();
        m_actualHealth->draw();
        m_actualStamina->draw();
        m_actualSpeed->draw();
        m_actualStrength->draw();
        m_maximumHealth->draw();
        m_maximumStamina->draw();
        m_condition->draw();
    }
}

void
RatingsWidget::drag(const int, const int)
{}

void
RatingsWidget::drop(const int, const int)
{}
