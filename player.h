/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * player.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Battlefield;
class Game;
class Monster;
class Display;

#include <string>
#include <ncurses.h>
#include "battlefield.h"
#include "game.h"

class Player
{
	static const uint8_t START_LEVEL =		1;
	static const uint8_t START_EXP =		0;
	static const uint8_t START_MAX_EXP =	4;
	static const uint8_t START_DAMAGE =		5;
	static const uint8_t START_MAX_HP =		10;
	static const uint8_t START_MAX_MANA =	10;
	static const uint8_t SIGHT_RADIUS =		2;

	static const uint8_t ADD_MAXHP_PER_LVL =   10;
	static const uint8_t ADD_DAMAGE_PER_LVL =	5;
	static const uint8_t EXP_TO_NEXT_LVL_MULTIPLIER = 2;

	public:
		Player(Battlefield *);
//		Player(const Player &);
		void Act(int);
		void LookAround();
		void Move(Field *);
		void SetMana(uint8_t);
		void Recover();
		void RecoverBy(uint8_t);
		void SpendMana(uint8_t);
		void SetHP(uint8_t);
		void Heal();
		void HealBy(uint8_t);
		void TakeDamage(uint8_t);
		void GainExp(Monster *);
		void LevelUp();
		void BoostHP(uint8_t);
		void BoostMana(uint8_t);
		void BoostDamage(uint8_t);
		void SetTargetField(Field *);
		void SetDisplay(Display *);

		Field* GetTargetField() const;
		Field* GetPosition() const;
		std::string GetName() const;
		uint8_t GetLevel() const;
		uint16_t GetExp() const;
		uint16_t GetExpMax() const;
		uint8_t GetDamage() const;
		uint8_t GetHP() const;
		uint8_t GetMaxHP() const;
		uint8_t GetMana() const;
		uint8_t GetMaxMana() const;

		bool IsAlive() const;
		bool IsDead() const;
		bool HaveTarget() const;

		void TEST_LevelUp();

	private:
		std::string m_name;
		uint8_t m_level;
		uint16_t m_exp;
		uint16_t m_expMax;
		uint8_t m_damage;
		uint8_t m_HP, m_maxHP;
		uint8_t m_mana, m_maxMana;
		uint8_t m_sightRadius;

		Battlefield *m_battlefield;
		Field *m_position;
		Field *m_target;
		Display *m_display;

		bool InSightRadius(uint8_t, uint8_t);
};

#endif // _PLAYER_H_

