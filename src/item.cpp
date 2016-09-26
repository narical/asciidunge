//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// item.cpp
//

#include "headers/item.h"
#include "headers/field.h"



Item::Item() : _field(NULL)
{

}


Item::~Item()
{

}


void Item::SetPosition(Field * position)
{
	_field = position;
}


SwordOfReadiness::SwordOfReadiness()
{
	_name = "Sword of Readiness";
	_description = "Grants FIRST STRIKE ability";
}


SwordOfReadiness::~SwordOfReadiness()
{

}


void SwordOfReadiness::Use()
{

}


std::string Item::GetName() const
{
	return _name;
}


std::string Item::GetDescription() const
{
	return _description;
}

