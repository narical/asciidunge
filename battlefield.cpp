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
	uint8_t maxItemsCount = rand() % 5 + 5;
	m_enemies.reserve(MAX_ENEMY_COUNT);

	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
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
    
  uint8_t enemiesToSpawn = MAX_ENEMY_COUNT;
  while (enemiesToSpawn > 0)
	{
		uint8_t row = rand() % BF_SIZE;
		uint8_t col = rand() % BF_SIZE;
		if ( m_field[row][col]->HaveEnemy() ) continue;
    m_field[row][col]->SpawnEnemy( &this->m_enemies[ --enemiesToSpawn ] );
	}


	for (uint8_t i = 0; i < maxItemsCount; ++i)
	{
		uint8_t row = rand() % BF_SIZE;
		uint8_t col = rand() % BF_SIZE;
		m_field[row][col]->SpawnItem();
	}
}


Field * Battlefield::GetNextField(Field * currentField, direction dir) const
{
	uint8_t currentCol = currentField->GetCol();
	uint8_t currentRow = currentField->GetRow();
	uint8_t nextCol = currentCol;
	uint8_t nextRow = currentRow;

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


Field * Battlefield::GetField(uint8_t row, uint8_t col) const
{
	return m_field[row][col];
}


void Battlefield::SetPlayer(Player * plr)
{
	m_player = plr;
}


uint8_t Battlefield::GetSize() const
{
	return BF_SIZE;
}


std::vector<Monster> * Battlefield::GetEnemies()
{
	return &m_enemies;
}


void Battlefield::CreateEnemy(uint8_t level, uint8_t quantity)
{
	 for (uint8_t i = 0; i < quantity; ++i) m_enemies.push_back(Monster(level));
}

Battlefield::~Battlefield()
{
	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			delete(m_field[row][column]);

	//for (unsigned int i = 0; i < m_enemies.size(); ++i) delete(m_enemies[i]); Ask A1eks what to to
}

