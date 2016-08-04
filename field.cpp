/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * field.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "field.h"

Field::Field(int row, int col) :
	m_coordCol(col),
	m_coordRow(row),
	m_enemy(NULL),
	m_item("no item!"),
	m_mana(MANA_PER_FIELD),
	m_HP(HP_PER_FIELD),
	m_visible(false)
{ }


int Field::GetRow()
{
	return m_coordRow;
}

int Field::GetCol()
{
	return m_coordCol;
}

void Field::SpawnEnemy(Monster * nextEnemyFromPool)
{
   m_enemy = nextEnemyFromPool;
}

Monster * Field::GetEnemy()
{
   return m_enemy;
}

bool Field::HaveEnemy()
{
 return ((m_enemy != NULL) && m_enemy->IsAlive());
}

void Field::SpawnItem()
{
   m_item = "item";
}

std::string Field::GetItem()
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

int Field::GetMana()
{
	int res = m_mana;
	m_mana = 0;
	return res;
}


int Field::GetHP()
{
	int res = m_HP;
	m_HP = 0;
	return res;
}
		


