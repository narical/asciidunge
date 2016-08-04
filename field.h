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
	static const unsigned int HP_PER_FIELD = 2;
	static const unsigned int MANA_PER_FIELD = 2;
	
	public:
		Field (int, int);
		void MakeVisible();
		void SpawnEnemy(Monster *);
		void SpawnItem();
		int GetHP();
		int GetMana();
		bool HaveEnemy();
		bool HaveItem();
		bool IsVisible();
		Monster * GetEnemy();
		std::string GetItem();
		int GetCol();
		int GetRow();
		
	private:
		int m_coordCol;
		int m_coordRow;
		Monster * m_enemy;
		std::string m_item;
		int m_mana;
		int m_HP;
		bool m_visible;
};

#endif // _FIELD_H_

