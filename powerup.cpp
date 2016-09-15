/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * powerup.cpp
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */


#include "powerup.h"



PowerUp::PowerUp(PowerupType type) : m_type(type), m_field(NULL)
{

}



void PowerUp::TakeBy(Player * plr)
{
	switch (m_type)
	{
		case HEALTH:
			plr->IncreaseMaxHP(POWERUP_HEALTH_BONUS);
			break;

		case MANA:
			plr->IncreaseMaxMana(POWERUP_MANA_BONUS);
			break;

		case DAMAGE:
			plr->IncreaseDamage(POWERUP_DAMAGE_BONUS);
	}
}



PowerupType PowerUp::GetType()
{
	return m_type;
}
