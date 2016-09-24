/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * player.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "config.h"
#include <string>

class Battlefield;
class Monster;
class Display;
class Field;



class Player
{
	public:
		Player(Battlefield *);
//		Player(const Player &);
		void Act(int);
		void LookAround();
		void Move(Field *);
		void SetMana(uint16_t);
		void Recover();
		void RecoverBy(uint16_t);
		void SpendMana(uint16_t);
		void SetHP(uint16_t);
		void Heal();
		void HealBy(uint16_t);
		void TakeDamage(uint16_t);
		void GainExp(Monster *);
		void LevelUp();
		void BoostHP(uint16_t);
		void BoostMana(uint16_t);
		void BoostDamage(uint16_t);
		void SetTargetField(Field *);
		void SetDisplay(Display *);

		Field* GetTargetField() const;
		Field* GetPosition() const;
		std::string GetName() const;
		uint8_t GetLevel() const;
		uint16_t GetExp() const;
		uint16_t GetExpMax() const;
		uint16_t GetDamage() const;
		uint16_t GetHP() const;
		uint16_t GetMaxHP() const;
		uint16_t GetMana() const;
		uint16_t GetMaxMana() const;

		bool IsAlive() const;
		bool IsDead() const;
		bool HaveTarget() const;

		void TEST_LevelUp();

	private:
		std::string _name;
		uint8_t _level;
		uint16_t _exp;
		uint16_t _expMax;
		uint16_t _damage;
		uint16_t _HP, _maxHP;
		uint16_t _mana, _maxMana;
		uint16_t _sightRadius;

		Battlefield *_battlefield;
		Field *_position;
		Field *_target;
		Display *_display;

		bool InSightRadius(uint8_t, uint8_t);
};

#endif // _PLAYER_H_
