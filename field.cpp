/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "field.h"

Field::Field() :enemy("no enemy!"),
		item("no item!"),
		mana(1),
		HP(1),
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

int Field::GetMana()
{
	int res = this->mana;
	this->mana = 0;
	return res;
}


int Field::GetHP()
{
	int res = this->HP;
	this->HP = 0;
	return res;
}
								

void Field::Show() {
	if (this->visible == false) printw ("x");
	else {
		if (this->enemy != "no enemy!") printw ("e");
		else if (this->item != "no item!") printw ("*");
		else printw (".");
	}
}
