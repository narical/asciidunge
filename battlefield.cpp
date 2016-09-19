/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * battlefield.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */
#include <cstdlib>
#include "battlefield.h"



Battlefield::Battlefield() : _playerCopy(0), _enemyCopy(0)
{
	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			_field[row][column] = new Field(row, column);

	SpawnEnemies();
	SpawnPowerups();
}



Battlefield::~Battlefield()
{
	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			delete(_field[row][column]);

	if (_playerCopy != NULL) delete(_playerCopy);
	if (_enemyCopy != NULL) delete(_enemyCopy);
}



void Battlefield::SpawnEnemies()
{
	uint8_t enemiesToSpawn;
	for (uint8_t monsterLevel = 1; monsterLevel <= 10; ++monsterLevel)
	{
		enemiesToSpawn = MONSTERS_QUANTITY_BY_LEVEL[monsterLevel];
		while (enemiesToSpawn > 0)
		{
			Field *field = GetRandomField();
			if ( field->HaveEnemy() ) continue;
			field->SpawnEnemy(monsterLevel);
			enemiesToSpawn--;
		}
	}
}



void Battlefield::SpawnPowerups()
{
	uint8_t powerupsToSpawn;
	for (PowerupType type = HEALTH; type != DAMAGE; type = PowerupType(type + 1))
	{
		powerupsToSpawn = POWERUPS_QUANTITY_BY_TYPE[type];
		while (powerupsToSpawn > 0)
		{
			Field *field = GetRandomField();
			if ( field->HavePowerup() ) continue;
			field->SpawnPowerup(type);
			powerupsToSpawn--;
		}
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
	if (_playerCopy != 0) delete _playerCopy;
	if (_enemyCopy != 0) delete _enemyCopy;
	_playerCopy = new Player( *_player );
	_enemyCopy = new Monster( *( _player->GetTargetField()->GetEnemy() ) );

	Fight(_playerCopy, _enemyCopy);
}



void Battlefield::SetPlayer(Player * plr)
{
	_player = plr;
}


Player * Battlefield::GetPlayer() const
{
	return _player;
}


Player * Battlefield::GetPlayerCopy() const
{
	return _playerCopy;
}


Monster * Battlefield::GetEnemyCopy() const
{
	return _enemyCopy;
}


Field * Battlefield::GetField(uint8_t row, uint8_t col) const
{
	return _field[row][col];
}


Field * Battlefield::GetRandomField() const
{
	uint8_t row = rand() % BF_SIZE;
	uint8_t col = rand() % BF_SIZE;
	return _field[row][col];
}


uint8_t Battlefield::GetSize() const
{
	return BF_SIZE;
}

