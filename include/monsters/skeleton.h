//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// skeleton.h
//

#ifndef _SKELETON_H_
#define _SKELETON_H_
#include "monster.hpp"



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

#endif // _SKELETON_H_
