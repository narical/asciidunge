//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// golem.h
//

#ifndef _GOLEM_H_
#define _GOLEM_H_
#include "monster.hpp"



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

#endif // _GOLEM_H_
