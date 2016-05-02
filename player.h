/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * player.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ncurses.h"
class Game;
#include <string>
#include "battlefield.h"
#include "game.h"

class Player
{
public:
	Player();
	void Show();
	void LookAround(Battlefield *);
	void Move(Battlefield *, int);
	void SetMana(int);
	void SetManaFull();
	void AddMana(int);
	void LoseMana(int);
	void SetHP(int);
	void SetHpFull();
	void AddHP(int);
	void LoseHP(int);

/*	TODO: реализовать оставшиеся методы класса Player
	std::string GetName();
	void SetHP();
	void AddHP();
	void LoseHP();
				
	void NextLevelExp();
	 
	void Kill();*/
	 
private:
	int level;
	int exp;
	int damage;
	int HP, maxHP;
	int mana, maxMana;
	int sightRadius;
	int coordRow;
	int coordCol;
	std::string name;
	
};

#endif // _PLAYER_H_

