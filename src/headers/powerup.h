//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// powerup.h
//

#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "config.h"
class Field;


class Powerup
{
	public:
		Powerup(poweruptype);
		poweruptype GetType();
		void SetPosition(Field *);

	private:
		poweruptype _type;
		Field * _field;
};

#endif // _POWERUP_H_
