//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// field.cpp
//

#include "headers/field.h"
#include "headers/player.h"
#include "headers/monster.h"
#include "headers/powerup.h"
#include "headers/item.h"



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


void Field::SpawnItem()
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


void Field::SpawnPowerup(poweruptype type)
{
	_powerup = new Powerup(type);
//	_powerup->SetPosition(this);
}


void Field::RemovePowerup()
{
	_powerup = NULL;
}


void Field::AddItem(Item * itm)
{
	_item = itm;
}


void Field::RemoveItem()
{
	_item = NULL;
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


Item * Field::GetItem() const
{
	return _item;
}

bool Field::HaveItem() const
{
	return (_item != NULL);
}


bool Field::MakeVisible()
{
	bool result = _visible;
	_visible = true;
	return !result; //return TRUE if we just made this field visible
}


bool Field::IsVisible() const
{
	return _visible;
}

