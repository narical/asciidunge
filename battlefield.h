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
	static const unsigned int BF_SIZE = 20;
	static const unsigned int MAX_ENEMY_COUNT = 39;

	public:
		Battlefield();
		~Battlefield();
	 	void CreateEnemy(int, int);
		Field * GetField(int, int) const;
		Field * GetNextField(Field *, direction) const;
		unsigned int GetSize() const; 
		void SetPlayer(Player *);
		std::vector<Monster> * GetEnemies();
		 
	private:
		Field *m_field[BF_SIZE][BF_SIZE];
		Player *m_player;
		std::vector<Monster> m_enemies;
};

#endif // _BATTLEFIELD_H_

