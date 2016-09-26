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

}


SwordOfReadiness::~SwordOfReadiness()
{

}


void SwordOfReadiness::Use()
{

}

