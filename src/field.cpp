//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// field.cpp
//

#include "field.hpp"
#include "player.hpp"
#include "item.hpp"
#include "monster.hpp"
#include <cassert>



Field::Field(uint8_t row, uint8_t col) :
	_coordCol(col),
	_coordRow(row),
	_enemy(nullptr),
	_powerup(nullptr),
	_item(nullptr),
	_visible(false)
{ }


Field::~Field()
{
	if (_enemy != nullptr) delete(_enemy);
	if (_powerup != nullptr) delete(_powerup);
	if (_item != nullptr) delete(_item);
}


/*
Field::Field (const Field &f)
{
	_coordCol = f._coordCol;
	_coordRow = f._coordRow;
	_enemy = nullptr;				//new Monster(*(f._enemy));
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
	bool wasAlreadyVisible = IsVisible();
	_visible = true;
	return !(wasAlreadyVisible); //return TRUE if we just made this field visible
}



void Field::SpawnPowerup(Powerups type)
{
	assert(_powerup == nullptr);
	_powerup = new Powerup(type);
}



void Field::RemovePowerup()
{
	assert(_powerup != nullptr);
	_powerup = nullptr;
	//TODO: fix logic after changing all pointers to std::unique_ptr
}