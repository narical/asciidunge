/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * powerup.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _POWERUP_H_
#define _POWERUP_H_
enum PowerupType {HEALTH, MANA, DAMAGE};

#include "display.h"
class Field;
class Player;




class Powerup
{
	public:
		Powerup(PowerupType);
		EventType TakeBy(Player *);
		PowerupType GetType();
		void SetPosition(Field *);
		 
	private:
		PowerupType _type;
		Field * _field;
		const uint8_t POWERUP_HEALTH_BONUS = 10;
		const uint8_t POWERUP_MANA_BONUS = 7;
		const uint8_t POWERUP_DAMAGE_BONUS = 5;
};

#endif // _POWERUP_H_
