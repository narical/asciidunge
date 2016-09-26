//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// powerup.cpp
//

#include "headers/powerup.h"
#include "headers/field.h"
#include "headers/player.h"



Powerup::Powerup(poweruptype type) : _type(type), _field(NULL)
{

}



void Powerup::SetPosition(Field * position)
{
	_field = position;
}



poweruptype Powerup::GetType()
{
	return _type;
}
