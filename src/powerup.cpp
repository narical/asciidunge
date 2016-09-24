/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * powerup.cpp
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "headers/powerup.h"
#include "headers/field.h"
#include "headers/player.h"



Powerup::Powerup(poweruptype type) : _type(type), _field(NULL)
{

}



eventtype Powerup::TakeBy(Player * plr)
{
	switch (_type)
	{
		case HEALTH:
			plr->BoostHP(POWERUP_HEALTH_BONUS);
			_field->RemovePowerup();
			return HP_PWRUP;

		case MANA:
			plr->BoostMana(POWERUP_MANA_BONUS);
			_field->RemovePowerup();
			return MANA_PWRUP;
			
		case DAMAGE:
			plr->BoostDamage(POWERUP_DAMAGE_BONUS);
			_field->RemovePowerup();
			return DMG_PWRUP;
	}
	
	// To get rid of compiler warning about non-void function returns nothing
	return EVENTS_END;
}



void Powerup::SetPosition(Field * position)
{
	_field = position;
}



poweruptype Powerup::GetType()
{
	return _type;
}
