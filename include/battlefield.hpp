//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// battlefield.h
//

#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_

#include "config.hpp"
#include "monster.hpp"

class Game;
class Player;
class Field;
class Monster;


class Battlefield
{
	public:
		explicit Battlefield(Game *);
		~Battlefield();
		void SpawnItems();
	 	void SpawnEnemies();
		void SpawnPowerups();
		void CalculateNextFight();
		uint8_t CountNearObjects(Field *);
		void Fight(Player *, Monster *, bool);
		Field * GetNextField(Field *, direction) const;

		Field * GetRandomField() const { return _field[ rand() % BF_SIZE ][ rand() % BF_SIZE ]; }
		Field * GetField(uint8_t row, uint8_t col) const { return _field[row][col]; }
		Player * GetPlayerCopy() const { return _playerCopy; }
		Monster * GetEnemyCopy() const { return _enemyCopy; }
		bool BossIsAlive() const { return !_boss->IsDead(); }
		bool BossIsDead() const { return _boss->IsDead(); }
		void TEST_Reveal();

	private:
		Game *_game;
		Field *_field[BF_SIZE][BF_SIZE];
		Monster *_boss;

		// to store possible fight results
		Player *_playerCopy;
		Monster *_enemyCopy;
};

#endif // _BATTLEFIELD_H_

