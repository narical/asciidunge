/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * battlefield.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_

#include <vector>
#include "monster.h"
class Player;
class Monster;
class Game;
class Field;
enum direction {LEFT, RIGHT, UP, DOWN};

class Battlefield {
	static const uint8_t BF_SIZE = 20;
	static const uint8_t MAX_ENEMY_COUNT = 39;

	public:
		Battlefield();
		~Battlefield();
	 	void CreateEnemy(uint8_t, uint8_t);
		Field * GetField(uint8_t, uint8_t) const;
		Field * GetNextField(Field *, direction) const;
		uint8_t GetSize() const; 
		void SetPlayer(Player *);
		Player * GetPlayerCopy();
		Monster * GetEnemyCopy();
		void Fight(Player *, Monster *);
		void CalculateNextFight();

		std::vector<Monster> * GetEnemies();
		 
	private:
		Field *m_field[BF_SIZE][BF_SIZE];
		Player *m_player;
		std::vector<Monster> m_enemies;
		
		// to store possible fight results
		Player *m_playerCopy;
		Monster *m_enemyCopy;
		
		
};

#endif // _BATTLEFIELD_H_

