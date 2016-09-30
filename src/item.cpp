//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// item.cpp
//

#include "headers/item.h"
#include "headers/field.h"
#include "headers/player.h"



Item::Item() : _state(NOT_SET), _field(NULL)
{

}


Item::~Item()
{

}


void Item::Use(Player * player)
{

}


void Item::SetPosition(Field * position)
{
	_field = position;
}


void Item::SetState(itemstate state)
{
	_state = state;
}


std::string Item::GetName() const
{
	return _name;
}


itemstate Item::GetState() const
{
	return _state;
}


std::string Item::GetDescription() const
{
	return _description;
}


uint8_t Item::GetManaCost() const
{
	return _manaCost;
}


SwordOfReadiness::SwordOfReadiness() : Item()
{
	_name = "Sword of Readiness";
	_description = "Grants FIRST STRIKE ability";
	_manaCost = 3;
}


SwordOfReadiness::~SwordOfReadiness()
{

}


MightyStrike::MightyStrike() : Item()
{
	_name = "Mighty Strike";
	_description = "This powerful blow grants 30% bonus damage";
}


MightyStrike::~MightyStrike()
{

}


Fireball::Fireball() : Item()
{
	_name = "Fireball";
	_description = "Fire death from above!";
}


Fireball::~Fireball()
{

}


Heal::Heal() : Item()
{
	_name = "Tome of healing";
	_description = "Healing power of magic";
}


Heal::~Heal()
{

}


EnergyShield::EnergyShield() : Item()
{
	_name = "Energy Shield";
	_description = "Let's magic defend you";
}


EnergyShield::~EnergyShield()
{

}


void SwordOfReadiness::Use(Player * player)
{
	switch (_state)
	{
		case PREPARED:
			player->SetInitiative(_bonus_initiative);
			_state = ACTIVE;
			break;

		case ACTIVE:
			player->SetInitiative(-_bonus_initiative);
			_state = NOT_SET;
			break;

		case NOT_SET:;
	}
}

