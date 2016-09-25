/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "headers/field.h"
#include "headers/monster.h"



Field::Field(uint8_t row, uint8_t col) :
	_coordCol(col),
	_coordRow(row),
	_enemy(NULL),
	_powerup(NULL),
	_item("no item!"),
	_mana(MANA_PER_FIELD),
	_HP(HP_PER_FIELD),
	_visible(false)
{ }


Field::~Field()
{
	if (_enemy != NULL) delete(_enemy);
	if (_powerup != NULL) delete(_powerup);
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


uint8_t Field::GetRow() const
{
	return _coordRow;
}


uint8_t Field::GetCol() const
{
	return _coordCol;
}


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


void Field::SpawnPowerup(poweruptype type)
{
   _powerup = new Powerup(type);
   _powerup->SetPosition(this);
}


void Field::RemovePowerup()
{
	_powerup = NULL;
}


Monster * Field::GetEnemy() const
{
   return _enemy;
}


Powerup * Field::GetPowerup() const
{
   return _powerup;
}


bool Field::HaveEnemy() const
{
 return ((_enemy != NULL) && _enemy->IsAlive());
}


bool Field::HavePowerup() const
{
 return (_powerup != NULL);
}


void Field::SpawnItem()
{
   _item = "item";
}


std::string Field::GetItem() const
{
   return _item;
}

bool Field::HaveItem() const
{
 return (GetItem() != "no item!");
}


void Field::MakeVisible()
{
   _visible = true;
}


bool Field::IsVisible() const
{
 return _visible;
}


uint16_t Field::ExtractMana()
{
	uint16_t res = _mana;
	_mana = 0;
	return res;
}


uint16_t Field::ExtractHP()
{
	uint16_t res = _HP;
	_HP = 0;
	return res;
}

