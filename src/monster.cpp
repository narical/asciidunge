//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// monster.cpp
//

#include "monster.hpp"
#include "player.hpp"
#include "field.hpp"



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

