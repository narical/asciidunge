//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include "config.hpp"
#include "powerup.hpp"
#include "monster.hpp"
#include <string>

class Player;
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

		void SpawnItem();
		void TEST_SpawnItem(uint8_t);
		void SpawnPowerup(Powerup::Type type);
		void RemovePowerup();

		bool HaveEnemy() const { return ((_enemy != nullptr) && _enemy->IsAlive()); }
		bool HavePowerup() const { return (_powerup != nullptr); }
		bool HaveItem() const { return (_item != nullptr); }
		void AddItem(Item * item) { _item = item; }
		void RemoveItem() { _item = nullptr; }
		bool IsVisible() const { return _visible; }
		Monster * GetEnemy() const { return _enemy; }
		Powerup * GetPowerup() const { return _powerup; }
		Item * GetItem() const { return _item; }
		uint8_t GetCol() const { return _coordCol; }
		uint8_t GetRow() const { return _coordRow; }

	private:
		uint8_t _coordCol;
		uint8_t _coordRow;
		Monster * _enemy;
		Powerup * _powerup;
		Item * _item;
		bool _visible;
};

#endif // _FIELD_H_

