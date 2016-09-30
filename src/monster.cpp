//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// monster.cpp
//

#include "headers/monster.h"
#include "headers/player.h"
#include "headers/field.h"



Monster::Monster(uint8_t monsterLevel) :
_level( monsterLevel ), _initiative(0), _isDead(0)
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


bool Monster::IsDead() const
{
	return _isDead;
}


bool Monster::IsAlive() const
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


uint16_t Monster::GetInitiative() const
{
	return _level + _initiative;
}

