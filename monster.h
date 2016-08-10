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
	Monster(uint8_t);
//	Monster(const Monster &);
	static uint8_t s_Quantity;
	void Attack(Player *);
	void AddHP(uint8_t);
	void TakeDamage(Player *);
	bool IsDead();
	bool IsAlive();

	std::string GetName() const;
	uint8_t GetLevel() const;
	uint8_t GetDamage() const;
	uint8_t GetHP() const;
	uint8_t GetMaxHP() const;
	 
private:

	uint8_t m_level;
	uint8_t m_exp;
	uint8_t m_damage;
	uint8_t m_HP;
	uint8_t m_maxHP;
	Field * m_field;
	std::string m_name;
	bool m_isDead;
	
	uint8_t CalculateDamage(uint8_t);
	uint8_t CalculateMaxHP(uint8_t);
};

#endif // _MONSTER_H_
