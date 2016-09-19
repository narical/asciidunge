/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * monster.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <string>
#include <stdint.h>
class Player;
class Field;



class Monster
{
	public:
		Monster(uint8_t);
	//	Monster(const Monster &);
		void Attack(Player *);
		void AddHP(uint16_t);
		void TakeDamage(Player *);
		bool IsDead();
		bool IsAlive();

		std::string GetName() const;
		uint8_t GetLevel() const;
		uint16_t GetDamage() const;
		uint16_t GetHP() const;
		uint16_t GetMaxHP() const;

	private:
		uint8_t _level;
		uint16_t _exp;
		uint16_t _damage;
		uint16_t _HP;
		uint16_t _maxHP;
		Field * _field;
		std::string _name;
		bool _isDead;

		uint16_t CalculateDamage(uint8_t);
		uint16_t CalculateMaxHP(uint8_t);
};

#endif // _MONSTER_H_
