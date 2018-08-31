//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// powerup.h
//

#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "config.hpp"

class Field;


class Powerup
{
	public:
		explicit Powerup(Powerups p) : _type(p), _field(nullptr) { }
		Powerups GetType() { return _type; }

	private:
		Powerups _type;
		Field * _field; //FIX: find out wtf
};

#endif // _POWERUP_H_
