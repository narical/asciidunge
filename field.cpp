/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "field.h"

Field::Field(uint8_t row, uint8_t col) :
	m_coordCol(col),
	m_coordRow(row),
	m_enemy(NULL),
	m_powerup(NULL),
	m_item("no item!"),
	m_mana(MANA_PER_FIELD),
	m_HP(HP_PER_FIELD),
	m_visible(false)
{ }


/*
Field::Field (const Field &f)
{
	m_coordCol = f.m_coordCol;
	m_coordRow = f.m_coordRow;
	m_enemy = NULL;				//new Monster(*(f.m_enemy));
	m_item = f.m_item;			//TODO: FIX AFTER "ITEM" CLASS IMPLEMENTATION !
	m_mana = f.m_mana;
	m_HP = f.m_HP;
	m_visible = f.m_visible;	
}
*/


uint8_t Field::GetRow() const
{
	return m_coordRow;
}

uint8_t Field::GetCol() const
{
	return m_coordCol;
}

void Field::SpawnEnemy(Monster * nextEnemyFromPool)
{
   m_enemy = nextEnemyFromPool;
}

void Field::SpawnPowerUp(PowerUp * nextPowerupFromPool)
{
   m_powerup = nextPowerupFromPool;
   m_powerup->SetPosition(this);
}


void Field::RemovePowerUp()
{
	m_powerup = NULL;
}


Monster * Field::GetEnemy() const
{
   return m_enemy;
}


PowerUp * Field::GetPowerup() const
{
   return m_powerup;
}


bool Field::HaveEnemy()
{
 return ((m_enemy != NULL) && m_enemy->IsAlive());
}

bool Field::HavePowerUp()
{
 return (m_powerup != NULL);
}

void Field::SpawnItem()
{
   m_item = "item";
}

std::string Field::GetItem() const
{
   return m_item;
}

bool Field::HaveItem()
{
 return (GetItem() != "no item!");
}

void Field::MakeVisible()
{
   m_visible = true;
}

bool Field::IsVisible()
{
 return m_visible;
}

uint8_t Field::GetMana()
{
	uint8_t res = m_mana;
	m_mana = 0;
	return res;
}


uint8_t Field::GetHP()
{
	uint8_t res = m_HP;
	m_HP = 0;
	return res;
}
		


