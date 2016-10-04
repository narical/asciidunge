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

