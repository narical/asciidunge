//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// mage.h
//

#ifndef _MAGE_H_
#define _MAGE_H_
#include <monster.h>



class Mage : public Monster
{
	public:
		Mage(uint8_t monsterLevel) : Monster(monsterLevel)
		{
			_damage = FromCurve( 4, 65 );
			_maxHP = FromCurve( 4, 83 );
			_HP = _maxHP;
			_name = "mage";
		}
};

#endif // _MAGE_H_
