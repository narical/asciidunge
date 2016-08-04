/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * player.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "player.h"


Player::Player (Battlefield *btl) :
m_level( START_LEVEL ),
m_exp( START_EXP ), m_expMax( START_MAX_EXP ),
m_damage( START_DAMAGE ),
m_HP( START_MAX_HP ), m_maxHP( START_MAX_HP ),
m_mana( START_MAX_MANA ), m_maxMana( START_MAX_MANA ), 
m_sightRadius( SIGHT_RADIUS ),
m_battlefield( btl ),
m_target( NULL ),
m_name( "Nameless hero" )
{
	m_battlefield->SetPlayer(this);
	Field *tempField = NULL;
	while (true)
	{
		int row = rand() % m_battlefield->GetSize();
		int col = rand() % m_battlefield->GetSize();
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
			Monster *targetEnemy = targetField->GetEnemy();
			targetEnemy->Attack(this);
			if (IsAlive())
			{
				targetEnemy->TakeDamage(this);
				if (targetEnemy->IsDead())
				{
					GainExp(targetEnemy);
					SetTarget(NULL);
				}
			}
		}
		else //if target was somewhere else
		{
			SetTarget(NULL);
			if (nextField->HaveEnemy()) SetTarget(nextField); //new target?
			else
			{
				m_position = nextField; //move and look around
				LookAround();
			}
		}
	}
}


void Player::LookAround()
{
	int radius	= m_sightRadius;
	int column	= m_position->GetCol();
	int row		= m_position->GetRow();

	int leftBorder		= column;
	int rightBorder		= column;
	int topBorder		= row;
	int bottomBorder	= row;
	int maxCoord		= m_battlefield->GetSize() - 1;

	for (int delta = 1; delta <= radius; ++delta)   // Crop sight rectangle to battlefield
	{
		if (leftBorder - delta <= 0) leftBorder = 0; else --leftBorder;
		if (rightBorder + delta >= maxCoord) rightBorder = maxCoord; else ++rightBorder;
		if (topBorder - delta <= 0) topBorder = 0; else --topBorder;
		if (bottomBorder + delta >= maxCoord) bottomBorder = maxCoord; else ++bottomBorder;
	}

	for (int tempRow = topBorder; tempRow <= bottomBorder; ++tempRow)
		for (int tempColumn = leftBorder; tempColumn <= rightBorder; ++tempColumn)
			if ( InSightRadius(tempRow, tempColumn) )
			{
				Field *field = m_battlefield->GetField(tempRow, tempColumn);
				field->MakeVisible();
				AddMana(field->GetMana());
				AddHP(field->GetHP());
			}
}


bool Player::InSightRadius(int testRow, int testColumn)
{
	int column  = m_position->GetCol();
	int row		= m_position->GetRow();
	int radius  = m_sightRadius;
	int deltaRow	= testRow - row;
	int deltaColumn = testColumn - column;

	return (deltaRow * deltaRow + deltaColumn * deltaColumn <= radius * radius);
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
}


void Player::SetMana(int newQuantity)
{
	m_mana = newQuantity;
	//TODO: добавить проверку
}


void Player::SetManaFull()
{
	m_mana = m_maxMana;
}


void Player::AddMana(int delta)
{
	m_mana = (m_mana + delta > m_maxMana ? m_maxMana : m_mana + delta);
}


void Player::LoseMana(int delta)
{
	m_mana = (m_mana - delta < 0 ? 0 : m_mana - delta);
}


void Player::SetHP(int newQuantity)
{
	m_HP = newQuantity;
	//TODO: добавить проверку
}


void Player::SetHpFull()
{
	m_HP = m_maxHP;
}


void Player::AddHP(int delta)
{
	m_HP = (m_HP + delta > m_maxHP ? m_maxHP : m_HP + delta);
}


void Player::LoseHP(int delta)
{
	m_HP = (m_HP - delta < 0 ? 0 : m_HP - delta);
}


void Player::SetTarget(Field * fld)
{
	m_target = fld;
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


int Player::GetLevel() const
{
	return m_level;
}


int Player::GetExp() const
{
	return m_exp;
}


int Player::GetExpMax() const
{
	return m_expMax;
}


int Player::GetDamage() const
{
	return m_damage;
}


int Player::GetHP() const
{
	return m_HP;
}


int Player::GetMaxHP() const
{
	return m_maxHP;
}


int Player::GetMana() const
{
	return m_mana;
}


int Player::GetMaxMana() const
{
	return m_maxMana;
}

