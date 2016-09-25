//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// battlefield.h
//

#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_

#include "config.h"
#include <stdint.h>


class Player;
class Field;
class Monster;
class Display;


class Battlefield
{
	public:
		Battlefield();
		~Battlefield();
	 	void SpawnEnemies();
		void SpawnPowerups();
		void SetPlayer(Player *);
		void CalculateNextFight();
		void SetDisplay(Display *);
		void Fight(Player *, Monster *, bool);

		Field * GetNextField(Field *, direction) const;
		Field * GetField(uint8_t, uint8_t) const;
		Field * GetRandomField() const;
		Player * GetPlayerCopy() const;
		Monster * GetEnemyCopy() const;
		Player * GetPlayer() const;
		uint8_t GetSize() const;
		bool BossIsAlive() const;
		bool BossIsDead() const;

	private:
		Field *_field[BF_SIZE][BF_SIZE];
		Display *_display;
		Player *_player;
		Monster *_boss;

  		// to store possible fight results
		Player *_playerCopy;
		Monster *_enemyCopy;
};

#endif // _BATTLEFIELD_H_

