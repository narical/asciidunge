//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// zombie.h
//

#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_
#include <monster.h>



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

#endif // _ZOMBIE_H_
