//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// powerup.cpp
//

#include "headers/powerup.h"
#include "headers/field.h"



Powerup::Powerup(poweruptype type) : _type(type), _field(NULL)
{

}



poweruptype Powerup::GetType()
{
	return _type;
}
