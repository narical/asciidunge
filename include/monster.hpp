//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// monster.h
//

#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "config.hpp"

class Player;
class Field;



class Monster
{
	public:
		Monster(uint8_t monsterLevel) : _level( monsterLevel ), _initiative(0), _isDead(0) { }

		void Attack(Player *);
		void AddHP(uint16_t);
		void TakeDamage(Player *);

		uint16_t GetInitiative() const { return _level + _initiative; }
		uint16_t GetDamage() const { return _damage; }
		std::string GetName() const { return _name; }
		uint16_t GetMaxHP() const { return _maxHP; }
		uint8_t GetLevel() const { return _level; }
		bool IsAlive() const { return !_isDead; }
		bool IsDead() const { return _isDead; }
		uint16_t GetHP() const { return _HP; }

	protected:
		uint8_t _level;
		uint16_t _damage;
		uint16_t _HP;
		uint16_t _maxHP;
		uint16_t _initiative;
		Field * _field;
		std::string _name;
		bool _isDead;

		uint16_t FromCurve(uint16_t, uint16_t);
};

#endif // _MONSTER_H_

