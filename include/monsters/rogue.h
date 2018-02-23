//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// rogue.h
//

#ifndef _ROGUE_H_
#define _ROGUE_H_
#include "monster.hpp"



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

#endif // _ROGUE_H_
