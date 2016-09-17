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



EventType PowerUp::TakeBy(Player * plr)
{
	switch (m_type)
	{
		case HEALTH:
			plr->BoostHP(POWERUP_HEALTH_BONUS);
			m_field->RemovePowerUp();
			return HP_PWRUP;

		case MANA:
			plr->BoostMana(POWERUP_MANA_BONUS);
			m_field->RemovePowerUp();
			return MANA_PWRUP;
			
		case DAMAGE:
			plr->BoostDamage(POWERUP_DAMAGE_BONUS);
			m_field->RemovePowerUp();
			return DMG_PWRUP;
	}
}



void PowerUp::SetPosition(Field * position)
{
	m_field = position;
}



PowerupType PowerUp::GetType()
{
	return m_type;
}
