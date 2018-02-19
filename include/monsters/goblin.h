//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// goblin.h
//

#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include <monster.h>



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

#endif // _GOBLIN_H_
