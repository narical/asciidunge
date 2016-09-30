//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// monster.h
//

#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <string>
#include <cstdint>

class Player;
class Field;



class Monster
{
	public:
		Monster(uint8_t);
	//	Monster(const Monster &);
		void Attack(Player *);
		void AddHP(uint16_t);
		void TakeDamage(Player *);

		std::string GetName() const;
		uint8_t GetLevel() const;
		uint16_t GetDamage() const;
		uint16_t GetHP() const;
		uint16_t GetMaxHP() const;
		uint16_t GetInitiative() const;
		bool IsDead() const;
		bool IsAlive() const;

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

