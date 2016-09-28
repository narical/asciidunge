//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// item.cpp
//

#include "headers/item.h"
#include "headers/field.h"



Item::Item() : _selected(false), _field(NULL)
{

}


Item::~Item()
{

}



void Item::Use()
{

}



void Item::SetPosition(Field * position)
{
	_field = position;
}



std::string Item::GetName() const
{
	return _name;
}



std::string Item::GetDescription() const
{
	return _description;
}




SwordOfReadiness::SwordOfReadiness()
{
	_name = "Sword of Readiness";
	_description = "Grants FIRST STRIKE ability";
}


SwordOfReadiness::~SwordOfReadiness()
{

}


MightyStrike::MightyStrike()
{
	_name = "Mighty Strike";
	_description = "This powerful blow grants 30% bonus damage";
}


MightyStrike::~MightyStrike()
{

}


Fireball::Fireball()
{
	_name = "Fireball";
	_description = "Fire death from above!";
}


Fireball::~Fireball()
{

}


Heal::Heal()
{
	_name = "Tome of healing";
	_description = "Healing power of magic";
}


Heal::~Heal()
{

}


EnergyShield::EnergyShield()
{
	_name = "Energy Shield";
	_description = "Let's magic defend you";
}


EnergyShield::~EnergyShield()
{

}


void SwordOfReadiness::Use()
{

}

