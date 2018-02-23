//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// powerup.h
//

#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "config.hpp"
#include <cstdio>
class Field;


class Powerup
{
	public:
		Powerup(poweruptype type) : _type(type), _field(nullptr) { }
		poweruptype GetType() { return _type; }

	private:
		poweruptype _type;
		Field * _field;
};

#endif // _POWERUP_H_
