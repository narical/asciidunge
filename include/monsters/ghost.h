//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// ghost.h
//

#ifndef _GHOST_H_
#define _GHOST_H_
#include <monster.h>



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

#endif // _GHOST_H_
