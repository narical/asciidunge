/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * battlefield.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */
#include <cstdlib>
#include "battlefield.h"


Battlefield::Battlefield()
{
	unsigned int maxItemsCount = rand() % 5 + 5;
	m_enemies.reserve(MAX_ENEMY_COUNT);

	for (int row = 0; row < BF_SIZE; ++row)
		for (int column = 0; column < BF_SIZE; ++column)
			m_field[row][column] = new Field(row, column); //TODO: free memory in destructor

	CreateEnemy(1,10);
	CreateEnemy(2,5);
	CreateEnemy(3,4);
	CreateEnemy(4,4);
	CreateEnemy(5,4);
	CreateEnemy(6,3);
	CreateEnemy(7,3);
	CreateEnemy(8,3);
	CreateEnemy(9,2);
	CreateEnemy(10,1);
    
  unsigned int enemiesToSpawn = MAX_ENEMY_COUNT;
  while (enemiesToSpawn > 0)
	{
		int row = rand() % BF_SIZE;
		int col = rand() % BF_SIZE;
		if ( m_field[row][col]->HaveEnemy() ) continue;
    m_field[row][col]->SpawnEnemy( &this->m_enemies[ --enemiesToSpawn ] );
	}


	for (unsigned int i = 0; i < maxItemsCount; ++i)
	{
		int row = rand() % BF_SIZE;
		int col = rand() % BF_SIZE;
		m_field[row][col]->SpawnItem();
	}
}


Field * Battlefield::GetNextField(Field * currentField, direction dir) const
{
	int currentCol = currentField->GetCol();
	int currentRow = currentField->GetRow();
	int nextCol = currentCol;
	int nextRow = currentRow;

	switch (dir)
	{
		case LEFT:
			if (currentCol > 0) --nextCol;
			break;
		case RIGHT:
			if (currentCol < BF_SIZE - 1) ++nextCol;
			break;
		case UP:
			if (currentRow > 0) --nextRow;
			break;
		case DOWN:
			if (currentRow < BF_SIZE - 1) ++nextRow;
	}
	Field *nextField = GetField(nextRow, nextCol);
	return nextField; 
}


Field * Battlefield::GetField(int row, int col) const
{
	return m_field[row][col];
}


void Battlefield::SetPlayer(Player * plr)
{
	m_player = plr;
}


unsigned int Battlefield::GetSize() const
{
	return BF_SIZE;
}


std::vector<Monster> * Battlefield::GetEnemies()
{
	return &m_enemies;
}


void Battlefield::CreateEnemy(int level, int quantity)
{
	 for (int i = 0; i < quantity; ++i) m_enemies.push_back(Monster(level));
}

