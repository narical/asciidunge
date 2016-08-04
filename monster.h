/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * monster.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _MONSTER_H_
#define _MONSTER_H_

class Battlefield;
class Game;
class Player;
class Field;
#include <string>
#include "battlefield.h"
#include "game.h"
#include "player.h"
#include "field.h"

class Monster
{
public:
	Monster(int);
	static int s_Quantity;
	void Attack(Player *);
	void AddHP(int);
	void TakeDamage(Player *);
	bool IsDead();
	bool IsAlive();

	std::string GetName() const;
	int GetLevel() const;
	int GetDamage() const;
	int GetHP() const;
	int GetMaxHP() const;
	 
private:

	int m_level;
	int m_exp;
	int m_damage;
	int m_HP;
	int m_maxHP;
	Field * m_field;
	std::string m_name;
	bool m_isDead;
	
	int CalculateDamage(int);
	int CalculateMaxHP(int);
};

#endif // _MONSTER_H_
