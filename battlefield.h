/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * battlefield.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_
enum direction {LEFT, RIGHT, UP, DOWN};

#include <stdint.h>


class Player;
class Field;
class Monster;


class Battlefield
{
	static const uint8_t BF_SIZE = 20;

	public:
		Battlefield();
		~Battlefield();
	 	void SpawnEnemies();
		void SpawnPowerups();
		Field * GetField(uint8_t, uint8_t) const;
		Field * GetRandomField() const;
		Field * GetNextField(Field *, direction) const;
		uint8_t GetSize() const;
		void SetPlayer(Player *);
		Player * GetPlayer() const;
		Player * GetPlayerCopy() const;
		Monster * GetEnemyCopy() const;
		void Fight(Player *, Monster *);
		void CalculateNextFight();
		bool BossIsAlive();
		bool BossIsDead();

	private:
		Field *_field[BF_SIZE][BF_SIZE];
		Player *_player;
		Monster *_boss;

  		// to store possible fight results
		Player *_playerCopy;
		Monster *_enemyCopy;

		const uint8_t POWERUPS_QUANTITY_BY_TYPE[3] = {5,5,5}; //health, mana, damage
		const uint8_t MONSTERS_QUANTITY_BY_LEVEL[11] = {0,10,5,4,4,4,3,3,3,2,1}; //Quantity of monsters of each level
		const uint8_t MAX_ENEMY_COUNT =  39;
};

#endif // _BATTLEFIELD_H_

