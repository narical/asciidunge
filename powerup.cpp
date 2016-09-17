/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * powerup.cpp
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */


#include "powerup.h"



Powerup::Powerup(PowerupType type) : m_type(type), m_field(NULL)
{

}



EventType Powerup::TakeBy(Player * plr)
{
	switch (m_type)
	{
		case HEALTH:
			plr->BoostHP(POWERUP_HEALTH_BONUS);
			m_field->RemovePowerup();
			return HP_PWRUP;

		case MANA:
			plr->BoostMana(POWERUP_MANA_BONUS);
			m_field->RemovePowerup();
			return MANA_PWRUP;
			
		case DAMAGE:
			plr->BoostDamage(POWERUP_DAMAGE_BONUS);
			m_field->RemovePowerup();
			return DMG_PWRUP;
	}
}



void Powerup::SetPosition(Field * position)
{
	m_field = position;
}



PowerupType Powerup::GetType()
{
	return m_type;
}
