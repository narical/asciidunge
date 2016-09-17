/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * battlefield.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */
#include <cstdlib>
#include "battlefield.h"


Battlefield::Battlefield() : m_playerCopy(0), m_enemyCopy(0)
{
	uint8_t maxItemsCount = rand() % 5 + 5;
	m_enemies.reserve(MAX_ENEMY_COUNT);

	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			m_field[row][column] = new Field(row, column); //TODO: free memory in destructor

	for (uint8_t monsterLevel = 1; monsterLevel <= 10; ++monsterLevel)
		CreateEnemy(monsterLevel, QUANTITY_OF_LEVEL[monsterLevel]);
  
	CreatePowerup(HEALTH, POWERUPS_HP_COUNT);
	CreatePowerup(MANA, POWERUPS_MANA_COUNT);
	CreatePowerup(DAMAGE, POWERUPS_DAMAGE_COUNT);
    
  uint8_t enemiesToSpawn = MAX_ENEMY_COUNT, row, col;
  while (enemiesToSpawn > 0)
	{
		row = rand() % BF_SIZE;
		col = rand() % BF_SIZE;
		if ( m_field[row][col]->HaveEnemy() ) continue;
		m_field[row][col]->SpawnEnemy( &this->m_enemies[ --enemiesToSpawn ] );
	}

  uint8_t powerupsToSpawn = MAX_POWERUPS_COUNT;
  while (powerupsToSpawn > 0)
	{
		row = rand() % BF_SIZE;
		col = rand() % BF_SIZE;
		if ( m_field[row][col]->HavePowerup() ) continue;
		m_field[row][col]->SpawnPowerup( &this->m_powerups[ --powerupsToSpawn ] );
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


void Battlefield::Fight(Player * player, Monster * enemy)
{
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
				player->SetTargetField(NULL);
			}
		}
	}
	else
	{
		enemy->TakeDamage(player);
		if (enemy->IsDead())
		{
			player->GainExp(enemy);
			player->SetTargetField(NULL);
		}
		else
		{
			enemy->Attack(player);
		}
	}
}


void Battlefield::CalculateNextFight()
{
	if (m_playerCopy != 0) delete m_playerCopy;
	if (m_enemyCopy != 0) delete m_enemyCopy;
	m_playerCopy = new Player( *m_player );
	m_enemyCopy = new Monster( *( m_player->GetTargetField()->GetEnemy() ) );
	
	Fight(m_playerCopy, m_enemyCopy);
}


void Battlefield::CreateEnemy(uint8_t level, uint8_t quantity)
{
	 for (uint8_t i = 0; i < quantity; ++i) m_enemies.push_back(Monster(level));
	 Monster::s_Quantity += quantity;
}


void Battlefield::CreatePowerup(PowerupType type, uint8_t quantity)
{
	 for (uint8_t i = 0; i < quantity; ++i) m_powerups.push_back(Powerup(type));
}


Player * Battlefield::GetPlayer()
{
	return m_player;
}


Player * Battlefield::GetPlayerCopy()
{
	return m_playerCopy;
}


Monster * Battlefield::GetEnemyCopy()
{
	return m_enemyCopy;
}


Battlefield::~Battlefield()
{
	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			delete(m_field[row][column]);

	//for (unsigned int i = 0; i < m_enemies.size(); ++i) delete(m_enemies[i]); Ask A1eks what to to
}

