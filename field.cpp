/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "field.h"

Field::Field() :enemy("no enemy!"),
		item("no item!"),
		mana(5),
		hp(7),
		visible(false)
{ }


void Field::SpawnEnemy()
{
   this->enemy = "goblin";
}

void Field::SpawnItem()
{
   this->item = "item";
}


void Field::MakeVisible()
{
   this->visible = true;
}


void Field::Show() {
	if (this->visible == false) printw ("x");
	else {
		if (this->enemy != "no enemy!") printw ("e");
		else if (this->item != "no item!") printw ("*");
		else printw (".");
	}
}
