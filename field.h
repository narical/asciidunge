/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _FIELD_H_
#define _FIELD_H_

#include "ncurses.h"
#include <iostream>
#include <string>


class Field
{
	public:
		Field ();
		void Show();
		void MakeVisible();
		void SpawnEnemy();
		void SpawnItem();
		int GetHP();
		int GetMana();
		
	private:
		std::string enemy;
		std::string item;
		int mana;
		int HP;
		bool visible;
};

#endif // _FIELD_H_

