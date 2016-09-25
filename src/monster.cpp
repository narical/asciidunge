//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// monster.cpp
//

#include "headers/monster.h"
#include "headers/player.h"
#include "headers/field.h"



Monster::Monster(uint8_t monsterLevel) : _level( monsterLevel ), _isDead(0)
{

}


/*
Monster::Monster(const Monster &p)
{
	_level = p._level;
	_exp = p._exp;
	_damage = p._damage;
	_HP = p._HP;
	_maxHP = p._maxHP;
	_field = NULL;
	_name = "111"; //p._name;
	_isDead = p._isDead;
}
*/



uint16_t Monster::FromCurve(uint16_t min, uint16_t max)
{
	if (_level == 1) return min;
	if (_level == 9) return max;
	if (_level == 10) return (uint16_t) max * 1.5;

	uint16_t full_delta = max - min;

	float result = min;
	for (uint8_t level = 2; level <= _level; ++level)
	{
		float rate = (float) CURVE_COEFF[level - 2] / SUM_COEFF;
		float delta = (float) full_delta * rate;
		result += delta;
	}
  return (uint16_t) result;
}



void Monster::Attack(Player * plr)
{
	plr->TakeDamage(_damage);
}


void Monster::AddHP(uint16_t delta)
{
	_HP = (_HP + delta > _maxHP ? _maxHP : _HP + delta);
}


void Monster::TakeDamage(Player * plr)
{
	uint16_t delta = plr->GetDamage();
	_HP = (_HP - delta < 0 ? 0 : _HP - delta);
	if (_HP == 0) _isDead = 1;
}


bool Monster::IsDead()
{
	return _isDead;
}


bool Monster::IsAlive()
{
	return !_isDead;
}


std::string Monster::GetName() const
{
	return _name;
}


uint8_t Monster::GetLevel() const
{
	return _level;
}


uint16_t Monster::GetDamage() const
{
	return _damage;
}


uint16_t Monster::GetHP() const
{
	return _HP;
}


uint16_t Monster::GetMaxHP() const
{
	return _maxHP;
}



//==============================================================//
//																//
//					BEGIN OF MONSTER SUBCLASSES					//
//																//
//==============================================================//



Goblin::Goblin(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 2, 52 );
	_maxHP = FromCurve( 4, 93 );
	_HP = _maxHP;
	_name = "goblin";
}



Skeleton::Skeleton(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 2, 25 );
	_maxHP = FromCurve( 3, 78 );
	_HP = _maxHP;
	_name = "skeleton";
}



Zombie::Zombie(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 4, 30 );
	_maxHP = FromCurve( 6, 125 );
	_HP = _maxHP;
	_name = "zombie";
}



Troll::Troll(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 2, 35 );
	_maxHP = FromCurve( 6, 140 );
	_HP = _maxHP;
	_name = "troll";
}



Rogue::Rogue(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 4, 60 );
	_maxHP = FromCurve( 3, 80 );
	_HP = _maxHP;
	_name = "rogue";
}



Mage::Mage(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 4, 65 );
	_maxHP = FromCurve( 4, 83 );
	_HP = _maxHP;
	_name = "mage";
}



Golem::Golem(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 1, 20 );
	_maxHP = FromCurve( 8, 200 );
	_HP = _maxHP;
	_name = "golem";
}



Ghost::Ghost(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = FromCurve( 4, 40 );
	_maxHP = FromCurve( 2, 174 );
	_HP = _maxHP;
	_name = "ghost";
}

