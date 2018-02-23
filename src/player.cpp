//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// player.cpp
//

#include "player.hpp"
#include <cassert>
#include <ncurses.h>
#include "battlefield.hpp"
#include "powerup.hpp"
#include "display.hpp"
#include "field.hpp"
#include "item.hpp"
#include "monster.hpp"
#include "game.hpp"



Player::Player (Game *game) :
_name( "Nameless hero" ),
_level( START_LEVEL ),
_initiative(0),
_selectedItem( nullptr ),
_target( nullptr ),
_game( game )
{
	_powerups[HEALTH] = 0;
	_powerups[MANA] = 0;
	_powerups[DAMAGE] = 0;
	for (uint8_t i = 0; i < 4; ++i) _inventory[i] = nullptr;
	Field *field = nullptr;
	while (true)
	{
		field = _game->GetBattlefield()->GetRandomField();
		if (field->HaveEnemy() || field->HaveItem() || field->HavePowerup() ) continue;
		break;
	}
	_position = field;

	CalculateStats();
	Heal();
	Recover();
	LookAround();
}



Player::Player (const Player &p)
{
	_name = p._name;
	_level = p._level;
	_exp = p._exp;
	_expMax = p._expMax;
	_damage = p._damage;
	_HP = p._HP;
	_maxHP = p._maxHP;
	_mana = p._mana;
	_maxMana = p._maxMana;
	_initiative = p._initiative;
	_position = p._position;
	_target = nullptr;
	_game = p._game;

	for (poweruptype type = HEALTH; type <= DAMAGE; type = poweruptype(type + 1))
		_powerups[type] = p._powerups[type];

	for (uint8_t i = 0; i < 4; ++i)
	{
		if (p._inventory[i] == nullptr) _inventory[i] = nullptr;
		else 
		{
			_inventory[i] = p._inventory[i]->Clone();
			if (p._selectedItem == p._inventory[i]) _selectedItem = _inventory[i];
		}
	}
}



void Player::CalculateStats()
{
	_maxHP		= _level * (HEALTH_PER_LEVEL + _powerups[HEALTH]);
	_maxMana	= _powerups[MANA] + START_MAX_MANA; 
	_damage		= _level * DAMAGE_PER_LEVEL * (1 + _powerups[DAMAGE] * (float) POWERUP_DAMAGE_BONUS /100 );
	_expMax		= _level * NEXT_LEVEL_MULTIPLIER;
}



void Player::Act(int input_key)
{
	Field *currentField = _position;
	Field *nextField = currentField;
	Field *targetField = GetTargetField();
	Battlefield *btl = _game->GetBattlefield();

	switch(input_key)
	{
		case KEY_LEFT:  nextField = btl->GetNextField(currentField, LEFT); break;
		case KEY_RIGHT:	nextField = btl->GetNextField(currentField, RIGHT); break;
		case KEY_UP:	nextField = btl->GetNextField(currentField, UP); break;
		case KEY_DOWN:  nextField = btl->GetNextField(currentField, DOWN);
	}

	if (nextField != nullptr) //if we're moving somewhere
	{
		if (nextField == targetField) //where our target is
		{
			btl->Fight(this, targetField->GetEnemy(), true); //Kill'em!
			if ( HaveTarget() ) btl->CalculateNextFight(); //if enemy still alive
		}
		else //if target was somewhere else
		{
			SetTargetField(nullptr); //forget about it

			if (nextField->HaveEnemy()) 
			{
				SetTargetField(nextField); // select new target if any
				btl->CalculateNextFight();
			}

			else if (nextField->HavePowerup())
			{
				_game->GetDisplay()->SendEvent( TakePowerup(nextField) );
			}

			else
			{
				_position = nextField; //if there's no enemy - move there and look around
				LookAround();
			}
		}
	}
}



void Player::LookAround()
{
	uint8_t column	= _position->GetCol();
	uint8_t row		= _position->GetRow();
	uint8_t maxCoord= BF_SIZE - 1;

	uint8_t leftBorder		= column > 0		? column - 1 : 0;
	uint8_t rightBorder		= column < maxCoord ? column + 1 : maxCoord;
	uint8_t topBorder		= row > 0			? row - 1 : 0;
	uint8_t bottomBorder	= row < maxCoord	? row + 1 : maxCoord;

	for (uint8_t tempRow = topBorder; tempRow <= bottomBorder; ++tempRow)
		for (uint8_t tempColumn = leftBorder; tempColumn <= rightBorder; ++tempColumn)
			{
				Field *field = _game->GetBattlefield()->GetField(tempRow, tempColumn);
				if (field->MakeVisible())
				{
					RecoverBy(MANA_PER_FIELD);
					HealBy(_level);
				}
			}
}



void Player::GainExp(Monster *enemy)
{
	uint8_t enemyLevel = enemy->GetLevel();
	uint8_t playerLevel = _level;
	uint8_t delta = (enemyLevel > playerLevel ? enemyLevel - playerLevel : 0);

	if (delta == 1) _exp += enemyLevel + 2;
	else _exp += enemyLevel + delta * delta;
	if (_exp >= _expMax) LevelUp();
}



void Player::LevelUp()
{
 	while (_exp >= _expMax)
 	{
 	 	_level++;
 	 	_exp -= _expMax;
		CalculateStats();
 	 	Heal();
 	 	Recover();
 	}
}



eventtype Player::TakePowerup(Field * field)
{
	poweruptype type = field->GetPowerup()->GetType();
	++_powerups[type];
	CalculateStats();
	field->RemovePowerup();
	
	eventtype result;
	switch (type)
	{
		case HEALTH:	result = HP_PWRUP; break;
		case MANA:		result = MANA_PWRUP; break;
		case DAMAGE:	result = DMG_PWRUP;
	}
	return result;
}



void Player::TakeItem()
{
	if (_position->GetItem() != nullptr)
	{
		Item * item = _position->GetItem();
		if (_inventory[0] == nullptr || _inventory[1] == nullptr ||
			_inventory[2] == nullptr || _inventory[3] == nullptr)
			{
				if		(_inventory[0] == nullptr) _inventory[0] = item;
				else if	(_inventory[1] == nullptr) _inventory[1] = item;
				else if	(_inventory[2] == nullptr) _inventory[2] = item;
				else if	(_inventory[3] == nullptr) _inventory[3] = item;
				_position->RemoveItem();
			}
			else if (_selectedItem != nullptr)
			{
				DropItem();
			}
	}
}



void Player::DropItem()
{
	if (_selectedItem != nullptr)
	{
		Item * pickItem = _position->GetItem();
		for (uint8_t i = 0; i < 4; ++i)
			if (_inventory[i] == _selectedItem) _inventory[i] = pickItem;
		_position->AddItem(_selectedItem);
		_selectedItem = pickItem;
	}
}



void Player::ActivateItem()
{
	if (_selectedItem != nullptr &&
		_mana >= _selectedItem->GetManaCost() &&
		_selectedItem->GetState() == NOT_SET)
	{
		_target = nullptr;
		_selectedItem->SetState(PREPARED);
		_mana -= _selectedItem->GetManaCost();
	}
}



void Player::HandleItems(std::string name)
{
	for (uint8_t i = 0; i < 4; ++i)
		if (_inventory[i] != nullptr && _inventory[i]->GetName() == name)
		{
			_inventory[i]->Use(this);
			break;
		}
}



// FOR TESTING

void Player::TEST_LevelUp()
{
	_exp = _expMax;
	LevelUp();
}

