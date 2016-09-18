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

	static bool bossIsDead;
	 
private:

	uint8_t _level;
	uint8_t _exp;
	uint8_t _damage;
	uint8_t _HP;
	uint8_t _maxHP;
	Field * _field;
	std::string _name;
	bool _isDead;
	
	uint8_t CalculateDamage(uint8_t);
	uint8_t CalculateMaxHP(uint8_t);
};

#endif // _MONSTER_H_
