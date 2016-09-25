//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// player.cpp
//

#include "headers/player.h"
#include <cassert>
#include <ncurses.h>
#include "headers/battlefield.h"
#include "headers/monster.h"
#include "headers/display.h"
#include "headers/field.h"



Player::Player (Battlefield *btl) :
_name( "Nameless hero" ),
_level( START_LEVEL ),
_exp( START_EXP ), _expMax( START_MAX_EXP ),
_damage( START_DAMAGE ),
_HP( START_MAX_HP ), _maxHP( START_MAX_HP ),
_mana( START_MAX_MANA ), _maxMana( START_MAX_MANA ),
_initiative(0),
_battlefield( btl ),
_target( NULL ),
_display( NULL )
{
	_battlefield->SetPlayer(this);
	Field *field = NULL;
	while (true)
	{
		field = _battlefield->GetRandomField();
		if (field->HaveEnemy() || field->HaveItem() || field->HavePowerup() ) continue;
		break;
	}
	_position = field;
  LookAround();
}


/*
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
	_sightRadius = p._sightRadius;

	_battlefield = p._battlefield;
	_display = p._display;
	_position = p._position;
	_target = NULL;
}
*/



void Player::Act(int input_key)
{
	Field *currentField = _position;
	Field *nextField = currentField;
	Field *targetField = GetTargetField();

	switch(input_key)
	{
		case KEY_LEFT:  nextField = _battlefield->GetNextField(currentField, LEFT); break;
		case KEY_RIGHT:	nextField = _battlefield->GetNextField(currentField, RIGHT); break;
		case KEY_UP:	nextField = _battlefield->GetNextField(currentField, UP); break;
		case KEY_DOWN:  nextField = _battlefield->GetNextField(currentField, DOWN);
	}

	if (nextField != currentField) //if we're moving somewhere
	{
		if (nextField == targetField) //where our target is
		{
			_battlefield->Fight(this, targetField->GetEnemy(), true); //Kill'em!
			if ( HaveTarget() ) _battlefield->CalculateNextFight(); //if enemy still alive
		}
		else //if target was somewhere else
		{
			SetTargetField(NULL); //forget about it

			if (nextField->HaveEnemy()) 
			{
				SetTargetField(nextField); // select new target if any
				_battlefield->CalculateNextFight();
			}

			else if (nextField->HavePowerup())
			{
				_display->SendEvent( nextField->GetPowerup()->TakeBy(this) );
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
	uint8_t maxCoord= _battlefield->GetSize() - 1;

	uint8_t leftBorder		= column > 0		? column - 1 : 0;
	uint8_t rightBorder		= column < maxCoord ? column + 1 : maxCoord;
	uint8_t topBorder		= row > 0			? row - 1 : 0;
	uint8_t bottomBorder	= row < maxCoord	? row + 1 : maxCoord;

	for (uint8_t tempRow = topBorder; tempRow <= bottomBorder; ++tempRow)
		for (uint8_t tempColumn = leftBorder; tempColumn <= rightBorder; ++tempColumn)
			{
				Field *field = _battlefield->GetField(tempRow, tempColumn);
				if (field->MakeVisible())
				{
					RecoverBy(1);
					HealBy(_level);
				}
			}
}


void Player::GainExp(Monster *enemy)
{
	int delta = enemy->GetLevel() - _level;
	int mult = (delta <= 0 ? 1 : delta + 1);
	_exp += enemy->GetLevel() * mult * 2;
	if (_exp >= _expMax) LevelUp();
}


void Player::LevelUp()
{
 	while (_exp >= _expMax)
 	{
 	 	_level++;
 	 	_exp -= _expMax;
 	 	_expMax *= EXP_TO_NEXT_LVL_MULTIPLIER;
 	 	_maxHP += ADD_MAXHP_PER_LVL;
 	 	_damage += ADD_DAMAGE_PER_LVL;
 	 	Heal();
 	 	Recover();
 	}
	// lvl-up animation works only if "real" player gets level-up
	if (this == _battlefield->GetPlayer()) _display->SendEvent(LVLUP);
}



void Player::BoostHP(uint16_t delta)
{
	_maxHP += delta;
	HealBy(delta);
}


void Player::BoostMana(uint16_t delta)
{
	_maxMana += delta;
	RecoverBy(delta);
}


void Player::BoostDamage(uint16_t delta)
{
	_damage += delta;
}


void Player::SetMana(uint16_t newQuantity)
{
	_mana = newQuantity;
	//TODO: добавить проверку
}


void Player::Recover()
{
	_mana = _maxMana;
}


void Player::RecoverBy(uint16_t delta)
{
	_mana = (_mana + delta > _maxMana ? _maxMana : _mana + delta);
}


void Player::SpendMana(uint16_t delta)
{
	_mana = (_mana - delta < 0 ? 0 : _mana - delta);
}


void Player::SetHP(uint16_t newQuantity)
{
	_HP = newQuantity;
	//TODO: добавить проверку
}


void Player::Heal()
{
	_HP = _maxHP;
}


void Player::HealBy(uint16_t delta)
{
	_HP = (_HP + delta > _maxHP ? _maxHP : _HP + delta);
}


void Player::TakeDamage(uint16_t delta)
{
	_HP = (_HP - delta < 0 ? 0 : _HP - delta);
}


void Player::SetTargetField(Field * fld)
{
	_target = fld;
}


void Player::SetDisplay(Display * dspl)
{
	_display = dspl;
}


Field * Player::GetTargetField() const
{
	return 	_target;
}


Field * Player::GetPosition() const
{
	return _position;
}


bool Player::IsAlive() const
{
	return _HP;
}


bool Player::IsDead() const
{
	return !IsAlive();
}


bool Player::HaveTarget() const
{
	return (_target != NULL);
}


std::string Player::GetName() const
{
	return _name;
}


uint8_t Player::GetLevel() const
{
	return _level;
}


uint16_t Player::GetExp() const
{
	return _exp;
}


uint16_t Player::GetExpMax() const
{
	return _expMax;
}


uint16_t Player::GetDamage() const
{
	return _damage;
}


uint16_t Player::GetHP() const
{
	return _HP;
}


uint16_t Player::GetMaxHP() const
{
	return _maxHP;
}


uint16_t Player::GetMana() const
{
	return _mana;
}


uint16_t Player::GetMaxMana() const
{
	return _maxMana;
}


uint16_t Player::GetInitiative() const
{
	return _level + _initiative;
}



// FOR TESTING

void Player::TEST_LevelUp()
{
	_exp = _expMax;
	LevelUp();
}

