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



class Ghost : public Monster
{
	public:
		Ghost(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 4, 40 );
			_maxHP = FromCurve( 2, 174 );
			_HP = _maxHP;
			_name = "ghost";
		}
};



class Goblin : public Monster
{
	public:
		Goblin(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 2, 52 );
			_maxHP = FromCurve( 4, 93 );
			_HP = _maxHP;
			_name = "goblin";
		}
};



class Golem : public Monster
{
	public:
		Golem(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 1, 33 );
			_maxHP = FromCurve( 8, 140 );
			_HP = _maxHP;
			_name = "golem";
		}
};



class Mage : public Monster
{
	public:
		Mage(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 4, 65 );
			_maxHP = FromCurve( 4, 83 );
			_HP = _maxHP;
			_name = "mage";
		}
};



class Rogue : public Monster
{
	public:
		Rogue(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 4, 60 );
			_maxHP = FromCurve( 3, 80 );
			_HP = _maxHP;
			_name = "rogue";
			_initiative = 10;
		}
};



class Skeleton : public Monster
{
	public:
		Skeleton(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 2, 25 );
			_maxHP = FromCurve( 3, 78 );
			_HP = _maxHP;
			_name = "skeleton";
		}
};



class Troll : public Monster
{
	public:
		Troll(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 2, 20 );
			_maxHP = FromCurve( 6, 200 );
			_HP = _maxHP;
			_name = "troll";
		}
};



class Zombie : public Monster
{
	public:
		Zombie(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 4, 30 );
			_maxHP = FromCurve( 6, 125 );
			_HP = _maxHP;
			_name = "zombie";
		}
};

#endif // _MONSTER_H_
