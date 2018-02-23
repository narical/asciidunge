//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// troll.h
//

#ifndef _TROLL_H_
#define _TROLL_H_
#include "monster.hpp"



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

#endif // _TROLL_H_
