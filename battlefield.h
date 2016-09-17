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
#include "powerup.h"
//class Player;
//class Monster;
//class PowerUp;
//class Game;
//class Field;
enum direction {LEFT, RIGHT, UP, DOWN};

class Battlefield {
	static const uint8_t BF_SIZE = 20;

	public:
		Battlefield();
		~Battlefield();
	 	void CreateEnemy(uint8_t, uint8_t);
		void CreatePowerUp(PowerupType, uint8_t);
		Field * GetField(uint8_t, uint8_t) const;
		Field * GetNextField(Field *, direction) const;
		uint8_t GetSize() const; 
		void SetPlayer(Player *);
		Player * GetPlayer();
		Player * GetPlayerCopy();
		Monster * GetEnemyCopy();
		void Fight(Player *, Monster *);
		void CalculateNextFight();

		std::vector<Monster> * GetEnemies();
		 
	private:
		Field *m_field[BF_SIZE][BF_SIZE];
		Player *m_player;
		std::vector<Monster> m_enemies;
		std::vector<PowerUp> m_powerups;
		
		// to store possible fight results
		Player *m_playerCopy;
		Monster *m_enemyCopy;
		
		const uint8_t POWERUPS_HP_COUNT = 5;
		const uint8_t POWERUPS_MANA_COUNT = 5;
		const uint8_t POWERUPS_DAMAGE_COUNT = 5;
		const uint8_t MAX_POWERUPS_COUNT = POWERUPS_HP_COUNT + POWERUPS_MANA_COUNT + POWERUPS_DAMAGE_COUNT;
		const uint8_t QUANTITY_OF_LEVEL[11] = {0,10,5,4,4,4,3,3,3,2,1}; //Quantity of monsters of each level
		const uint8_t MAX_ENEMY_COUNT =          10+5+4+4+4+3+3+3+2+1;


};

#endif // _BATTLEFIELD_H_

