/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * item.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _ITE_H_
#define _ITE_H_

#include <string>
#include <stdint.h>
class Player;
class Field;

class Item
{
public:
	Item();
	void TakeFunc();
	void DestroyFunc();
	void UseFunc();
	void GameplayFunc();

	 
private:
	std::string name;
	std::string desc;
	Player * _player;
	Field * _field;
	int manacost;

};

#endif // _ITE_H_
