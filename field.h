/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _FIELD_H_
#define _FIELD_H_

class Monster;
class Powerup;
class Battlefield;
#include <iostream>
#include <string>
#include "monster.h"
#include "powerup.h"

class Field
{
	static const uint8_t HP_PER_FIELD = 2;
	static const uint8_t MANA_PER_FIELD = 2;
	
	public:
		Field (uint8_t, uint8_t);
//		Field (const Field &);
		void MakeVisible();
		void SpawnEnemy(Monster *);
		void SpawnItem();
		void SpawnPowerup(Powerup *);
		void RemovePowerup();
		uint8_t GetHP();
		uint8_t GetMana();
		bool HaveEnemy();
		bool HavePowerup();
		bool HaveItem();
		bool IsVisible();
		Monster * GetEnemy() const;
		Powerup * GetPowerup() const;
		std::string GetItem() const;
		uint8_t GetCol() const;
		uint8_t GetRow() const;
		
	private:
		uint8_t _coordCol;
		uint8_t _coordRow;
		Monster * _enemy;
		Powerup * _powerup;
		std::string _item;
		uint8_t _mana;
		uint8_t _HP;
		bool _visible;
};

#endif // _FIELD_H_

