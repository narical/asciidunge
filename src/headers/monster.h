//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// monster.h
//

#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <string>
#include <stdint.h>
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


class Goblin : public Monster
{
	public:
		Goblin(uint8_t);
};


class Skeleton : public Monster
{
	public:
		Skeleton(uint8_t);
};


class Zombie : public Monster
{
	public:
		Zombie(uint8_t);
};


class Troll : public Monster
{
	public:
		Troll(uint8_t);
};


class Rogue : public Monster
{
	public:
		Rogue(uint8_t);
};


class Mage : public Monster
{
	public:
		Mage(uint8_t);
};


class Golem : public Monster
{
	public:
		Golem(uint8_t);
};


class Ghost : public Monster
{
	public:
		Ghost(uint8_t);
};


#endif // _MONSTER_H_

