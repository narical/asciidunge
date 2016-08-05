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
#include <string>
#include <ncurses.h>
#include "battlefield.h"
#include "game.h"

class Player
{
	static const unsigned int START_LEVEL =		1;
	static const unsigned int START_EXP =		0;
	static const unsigned int START_MAX_EXP =	4;
	static const unsigned int START_DAMAGE =	5;
	static const unsigned int START_MAX_HP =	10;
	static const unsigned int START_MAX_MANA =	10;
	static const unsigned int SIGHT_RADIUS =	2;

	static const unsigned int ADD_MAXHP_PER_LVL =   10;
	static const unsigned int ADD_DAMAGE_PER_LVL =	5;
	static const unsigned int EXP_TO_NEXT_LVL_MULTIPLIER =	2;

	public:
		Player(Battlefield *);
		void Act(int);
		void LookAround();
		void Move(Field *);
		void SetMana(int);
		void SetManaFull();
		void AddMana(int);
		void LoseMana(int);
		void SetHP(int);
		void SetHpFull();
		void AddHP(int);
		void LoseHP(int);
		void GainExp(Monster *);
		void LevelUp();
		void SetTarget(Field *);
		void SetDisplay(Display *);

		Field* GetTarget() const;
		Field* GetPosition() const;
		std::string GetName() const;
		int GetLevel() const;
		int GetExp() const;
		int GetExpMax() const;
		int GetDamage() const;
		int GetHP() const;
		int GetMaxHP() const;
		int GetMana() const;
		int GetMaxMana() const;

		bool IsAlive() const;
		bool HaveTarget() const;


		 
	private:
		std::string m_name;
		int m_level;
		int m_exp;
		int m_expMax;
		int m_damage;
		int m_HP, m_maxHP;
		int m_mana, m_maxMana;
		int m_sightRadius;

		Battlefield *m_battlefield;
		Field *m_position;
		Field *m_target;
		Display *m_display;


		bool InSightRadius(int, int);
};

#endif // _PLAYER_H_

