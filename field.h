/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _FIELD_H_
#define _FIELD_H_

class Monster;
class Battlefield;
#include <iostream>
#include <string>
#include "monster.h"

class Field
{
	static const uint8_t HP_PER_FIELD = 2;
	static const uint8_t MANA_PER_FIELD = 2;
	
	public:
		Field (uint8_t, uint8_t);
		void MakeVisible();
		void SpawnEnemy(Monster *);
		void SpawnItem();
		uint8_t GetHP();
		uint8_t GetMana();
		bool HaveEnemy();
		bool HaveItem();
		bool IsVisible();
		Monster * GetEnemy();
		std::string GetItem();
		uint8_t GetCol();
		uint8_t GetRow();
		
	private:
		uint8_t m_coordCol;
		uint8_t m_coordRow;
		Monster * m_enemy;
		std::string m_item;
		uint8_t m_mana;
		uint8_t m_HP;
		bool m_visible;
};

#endif // _FIELD_H_

