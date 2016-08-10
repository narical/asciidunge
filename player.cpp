/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * player.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "player.h"


Player::Player (Battlefield *btl) :
m_name( "Nameless hero" ),
m_level( START_LEVEL ),
m_exp( START_EXP ), m_expMax( START_MAX_EXP ),
m_damage( START_DAMAGE ),
m_HP( START_MAX_HP ), m_maxHP( START_MAX_HP ),
m_mana( START_MAX_MANA ), m_maxMana( START_MAX_MANA ), 
m_sightRadius( SIGHT_RADIUS ),
m_battlefield( btl ),
m_target( NULL ),
m_display( NULL )
{
	m_battlefield->SetPlayer(this);
	Field *tempField = NULL;
	while (true)
	{
		uint8_t row = rand() % m_battlefield->GetSize();
		uint8_t col = rand() % m_battlefield->GetSize();
		tempField = m_battlefield->GetField(row, col);
		if (!tempField->HaveEnemy() && !tempField->HaveItem()) break;
	}
	m_position = tempField;
}


void Player::Act(int input_key)
{
	Field *currentField = m_position;
	Field *nextField = currentField;
	Field *targetField = GetTarget();

	switch(input_key)
	{
		case KEY_LEFT:
			nextField = m_battlefield->GetNextField(currentField, LEFT);
			break;
		case KEY_RIGHT:
			nextField = m_battlefield->GetNextField(currentField, RIGHT);
			break;
		case KEY_UP:
			nextField = m_battlefield->GetNextField(currentField, UP);
			break;
		case KEY_DOWN:
			nextField = m_battlefield->GetNextField(currentField, DOWN);
	}

	if (nextField != currentField) // if we're moving somewhere
	{
		if (nextField == targetField) //where our target is
		{
			Fight(); //Kill'em!
		}
		else //if target was somewhere else
		{
			SetTarget(NULL); //forget about it

			if (nextField->HaveEnemy()) SetTarget(nextField); //and select new target if any
			else
			{
				m_position = nextField; //if not - move there and look around
				LookAround();
			}
		}
	}
}


void Player::LookAround()
{
	uint8_t radius	= m_sightRadius;
	uint8_t column	= m_position->GetCol();
	uint8_t row		= m_position->GetRow();

	uint8_t leftBorder		= column;
	uint8_t rightBorder		= column;
	uint8_t topBorder		= row;
	uint8_t bottomBorder	= row;
	uint8_t maxCoord		= m_battlefield->GetSize() - 1;

	for (uint8_t delta = 1; delta <= radius; ++delta)   // Crop sight rectangle to battlefield
	{
		if (leftBorder - delta <= 0) leftBorder = 0; else --leftBorder;
		if (rightBorder + delta >= maxCoord) rightBorder = maxCoord; else ++rightBorder;
		if (topBorder - delta <= 0) topBorder = 0; else --topBorder;
		if (bottomBorder + delta >= maxCoord) bottomBorder = maxCoord; else ++bottomBorder;
	}

	for (uint8_t tempRow = topBorder; tempRow <= bottomBorder; ++tempRow)
		for (uint8_t tempColumn = leftBorder; tempColumn <= rightBorder; ++tempColumn)
			if ( InSightRadius(tempRow, tempColumn) )
			{
				Field *field = m_battlefield->GetField(tempRow, tempColumn);
				field->MakeVisible();
				AddMana(field->GetMana());
				AddHP(field->GetHP());
			}
}


void Player::Fight()
{
	Monster *enemy = GetTarget()->GetEnemy();
	Player *player = this;
	uint8_t monsterLevel = enemy->GetLevel();
	uint8_t playerLevel = player->GetLevel();

	if (monsterLevel >= playerLevel)
	{
		enemy->Attack(player);

		if (player->IsAlive())
		{
			enemy->TakeDamage(player);

			if (enemy->IsDead())
			{
				player->GainExp(enemy);
				player->SetTarget(NULL);
			}
		}
	}
	else
	{
		enemy->TakeDamage(player);
		if (enemy->IsDead())
		{
			player->GainExp(enemy);
			player->SetTarget(NULL);
		}
		else
		{
			enemy->Attack(player);			
		}
	}
}


void Player::GainExp(Monster *enemy)
{
	int delta = enemy->GetLevel() - m_level;
	int mult = (delta <= 0 ? 1 : delta + 1);
	m_exp += enemy->GetLevel() * mult * 2;
	if (m_exp >= m_expMax) LevelUp();
}


void Player::LevelUp()
{
 	while (m_exp >= m_expMax)
 	{
 	 	m_level++;
 	 	m_exp -= m_expMax;
 	 	m_expMax *= EXP_TO_NEXT_LVL_MULTIPLIER;
 	 	m_maxHP += ADD_MAXHP_PER_LVL;
 	 	m_damage += ADD_DAMAGE_PER_LVL;
 	 	SetHpFull();
 	 	SetManaFull();
 	}
	m_display->SendEvent(LVLUP);
}


bool Player::InSightRadius(uint8_t testRow, uint8_t testColumn)
{
	uint8_t column  = m_position->GetCol();
	uint8_t row		= m_position->GetRow();
	uint8_t radius  = m_sightRadius;
	int deltaRow	= testRow - row;
	int deltaColumn = testColumn - column;

	return (deltaRow * deltaRow + deltaColumn * deltaColumn <= radius * radius);
}


void Player::SetMana(uint8_t newQuantity)
{
	m_mana = newQuantity;
	//TODO: добавить проверку
}


void Player::SetManaFull()
{
	m_mana = m_maxMana;
}


void Player::AddMana(uint8_t delta)
{
	m_mana = (m_mana + delta > m_maxMana ? m_maxMana : m_mana + delta);
}


void Player::LoseMana(uint8_t delta)
{
	m_mana = (m_mana - delta < 0 ? 0 : m_mana - delta);
}


void Player::SetHP(uint8_t newQuantity)
{
	m_HP = newQuantity;
	//TODO: добавить проверку
}


void Player::SetHpFull()
{
	m_HP = m_maxHP;
}


void Player::AddHP(uint8_t delta)
{
	m_HP = (m_HP + delta > m_maxHP ? m_maxHP : m_HP + delta);
}


void Player::LoseHP(uint8_t delta)
{
	m_HP = (m_HP - delta < 0 ? 0 : m_HP - delta);
}


void Player::SetTarget(Field * fld)
{
	m_target = fld;
}


void Player::SetDisplay(Display * dspl)
{
	m_display = dspl;
}


Field * Player::GetTarget() const
{
	return 	m_target;
}


Field * Player::GetPosition() const
{
	return m_position;
}


bool Player::IsAlive() const
{
	return m_HP;
}


bool Player::HaveTarget() const
{
	return (m_target != NULL);
}

std::string Player::GetName() const
{
	return m_name;
}


uint8_t Player::GetLevel() const
{
	return m_level;
}


uint8_t Player::GetExp() const
{
	return m_exp;
}


uint8_t Player::GetExpMax() const
{
	return m_expMax;
}


uint8_t Player::GetDamage() const
{
	return m_damage;
}


uint8_t Player::GetHP() const
{
	return m_HP;
}


uint8_t Player::GetMaxHP() const
{
	return m_maxHP;
}


uint8_t Player::GetMana() const
{
	return m_mana;
}


uint8_t Player::GetMaxMana() const
{
	return m_maxMana;
}

