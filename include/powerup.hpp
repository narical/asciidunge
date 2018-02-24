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
		enum Type {HEALTH, MANA, DAMAGE};
		explicit Powerup(Type t) : _type(t), _field(nullptr) { }
		Type GetType() { return _type; }

	private:
		Type _type;
		Field * _field; //FIX: find out wtf
};

#endif // _POWERUP_H_
