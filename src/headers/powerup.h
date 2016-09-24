/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * powerup.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "config.h"
class Field;
class Player;



class Powerup
{
	public:
		Powerup(poweruptype);
		eventtype TakeBy(Player *);
		poweruptype GetType();
		void SetPosition(Field *);

	private:
		poweruptype _type;
		Field * _field;
};

#endif // _POWERUP_H_
