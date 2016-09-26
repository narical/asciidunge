//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include "config.h"
#include <string>

class Monster;
class Powerup;
class Item;


class Field
{
	public:
		Field (uint8_t, uint8_t);
		~Field ();
//		Field (const Field &);
		bool MakeVisible();
		void SpawnEnemy(uint8_t);
		void SpawnPowerup(poweruptype);
		void SpawnItem();
		void RemovePowerup();
		bool HaveEnemy() const;
		bool HavePowerup() const;
		bool HaveItem() const;
		bool IsVisible() const;
		Monster * GetEnemy() const;
		Powerup * GetPowerup() const;
		Item * GetItem() const;
		uint8_t GetCol() const;
		uint8_t GetRow() const;
		
	private:
		uint8_t _coordCol;
		uint8_t _coordRow;
		Monster * _enemy;
		Powerup * _powerup;
		Item * _item;
		bool _visible;
};

#endif // _FIELD_H_

