//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// field.cpp
//

#include "headers/field.h"
#include "headers/player.h"
#include "headers/item.h"

#include "monsters/ghost.h"
#include "monsters/goblin.h"
#include "monsters/golem.h"
#include "monsters/mage.h"
#include "monsters/rogue.h"
#include "monsters/skeleton.h"
#include "monsters/troll.h"
#include "monsters/zombie.h"

#include "items/swordofreadiness.h"
#include "items/fireball.h"
#include "items/heal.h"
#include "items/energyshield.h"
#include "items/mightystrike.h"


Field::Field(uint8_t row, uint8_t col) :
	_coordCol(col),
	_coordRow(row),
	_enemy(NULL),
	_powerup(NULL),
	_item(NULL),
	_visible(false)
{ }


Field::~Field()
{
	if (_enemy != NULL) delete(_enemy);
	if (_powerup != NULL) delete(_powerup);
	if (_item != NULL) delete(_item);
}


/*
Field::Field (const Field &f)
{
	_coordCol = f._coordCol;
	_coordRow = f._coordRow;
	_enemy = NULL;				//new Monster(*(f._enemy));
	_item = f._item;			//TODO: FIX AFTER "ITEM" CLASS IMPLEMENTATION !
	_mana = f._mana;
	_HP = f._HP;
	_visible = f._visible;	
}
*/



void Field::SpawnEnemy(uint8_t monsterLevel)
{
	switch (rand() % 8)
	{
		case 0: _enemy = new Goblin(monsterLevel); break;
		case 1: _enemy = new Skeleton(monsterLevel); break;
		case 2: _enemy = new Zombie(monsterLevel); break;
		case 3: _enemy = new Troll(monsterLevel); break;
		case 4: _enemy = new Rogue(monsterLevel); break;
		case 5: _enemy = new Mage(monsterLevel); break;
		case 6: _enemy = new Golem(monsterLevel); break;
		case 7: _enemy = new Ghost(monsterLevel); break;
	}
}


void Field::SpawnItem()	//TODO: make spawn every item only once
{
	switch (rand() % 5)
	{
		case 0: _item = new SwordOfReadiness(); break;
		case 1: _item = new MightyStrike(); break;
		case 2: _item = new Fireball(); break;
		case 3: _item = new Heal(); break;
		case 4: _item = new EnergyShield(); break;
	}
}


void Field::TEST_SpawnItem(uint8_t num)
{
	switch (num)
	{
		case 1: _item = new SwordOfReadiness(); break;
		case 2: _item = new MightyStrike(); break;
		case 3: _item = new Fireball(); break;
		case 4: _item = new Heal(); break;
		case 5: _item = new EnergyShield(); break;
	}
}



bool Field::MakeVisible()
{
	bool result = _visible;
	_visible = true;
	return !result; //return TRUE if we just made this field visible
}

