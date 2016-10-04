//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// battlefield.cpp
//

#include "headers/battlefield.h"
#include "headers/player.h"
#include "headers/field.h"
#include "headers/display.h"
#include "headers/item.h"

#include "monsters/ghost.h"
#include "monsters/goblin.h"
#include "monsters/golem.h"
#include "monsters/mage.h"
#include "monsters/rogue.h"
#include "monsters/skeleton.h"
#include "monsters/troll.h"
#include "monsters/zombie.h"

Battlefield::Battlefield() : _boss(NULL), _playerCopy(NULL), _enemyCopy(NULL)
{
	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			_field[row][column] = new Field(row, column);

	SpawnEnemies();
	SpawnPowerups();
	SpawnItems();
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
			if ( field->HaveEnemy() ||
				CountNearObjects(field) > MAX_NEAR_OBJECTS ) continue;

			field->SpawnEnemy(monsterLevel);
			enemiesToSpawn--;

			if (monsterLevel == 10) _boss = field->GetEnemy();
		}
	}
}



void Battlefield::SpawnPowerups()
{
	uint8_t powerupsToSpawn;
	for (poweruptype type = HEALTH; type <= DAMAGE; type = poweruptype(type + 1))
	{
		powerupsToSpawn = POWERUPS_QUANTITY_BY_TYPE[type];
		while (powerupsToSpawn > 0)
		{
			Field *field = GetRandomField();
			if ( field->HavePowerup() ||
				CountNearObjects(field) > MAX_NEAR_OBJECTS ) continue;

			field->SpawnPowerup(type);
			powerupsToSpawn--;
		}
	}
}



void Battlefield::SpawnItems()
{
	uint8_t itemsToSpawn = ITEMS_QUANTITY;
	while (itemsToSpawn > 0)
	{
		Field *field = GetRandomField();
		if ( field->HavePowerup() || field->HaveItem() || field->HaveEnemy() ||
			CountNearObjects(field) > MAX_NEAR_OBJECTS ) continue;
		//field->SpawnItem();
		field->TEST_SpawnItem(itemsToSpawn);	// Can wait until v0.6a milestone
		itemsToSpawn--;
	}
}



Field * Battlefield::GetNextField(Field * currentField, direction dir) const
{
	uint8_t Col = currentField->GetCol();
	uint8_t Row = currentField->GetRow();
	bool notLeft = Col > 0;
	bool notTop = Row > 0;
	bool notRight = Col < BF_SIZE - 1;
	bool notBottom = Row < BF_SIZE - 1;

	switch (dir)
	{
		case LEFT:	if (notLeft) return GetField(Row, --Col);
			break;

		case RIGHT:	if (notRight) return GetField(Row, ++Col);
			break;

		case UP:	if (notTop) return GetField(--Row, Col);
			break;

		case DOWN:	if (notBottom) return GetField(++Row, Col);
			break;

		case UPLEFT: if (notTop && notLeft) return GetField(--Row, --Col);
			break;

		case UPRIGHT: if (notTop && notRight) return GetField(--Row, ++Col);
			break;

		case DOWNLEFT: if (notBottom && notLeft) return GetField(++Row, --Col);
			break;

		case DOWNRIGHT: if (notBottom && notRight) return GetField(++Row, ++Col);
			break;
	}
	return NULL;
}



void Battlefield::Fight(Player * player, Monster * enemy, bool realFight)
{
	player->HandleItems("Sword of Readiness");
	uint16_t monsterInitiative = enemy->GetInitiative();
	uint16_t playerInitiative = player->GetInitiative();

	if (monsterInitiative >= playerInitiative)
	{
		enemy->Attack(player);
		if (realFight) _display->SendEvent(PLR_HIT_1);

		if (player->IsAlive())
		{
			enemy->TakeDamage(player);
			if (realFight) _display->SendEvent(MNSTR_HIT_2);
			
			if (enemy->IsDead())
			{
				if (realFight) player->GainExp(enemy);
				player->SetTargetField(NULL);
			}
		}
	}
	else
	{
		enemy->TakeDamage(player);
		if (realFight) _display->SendEvent(MNSTR_HIT_1);

		if (enemy->IsDead())
		{
			if (realFight) player->GainExp(enemy);
			player->SetTargetField(NULL);
		}
		else
		{
			enemy->Attack(player);
			if (realFight) _display->SendEvent(PLR_HIT_2);
		}
	}
	player->HandleItems("Sword of Readiness");
}



void Battlefield::CalculateNextFight()
{
	if (_playerCopy != 0) delete _playerCopy;
	if (_enemyCopy != 0) delete _enemyCopy;
	_playerCopy = new Player( *_player );
	_enemyCopy = new Monster( *( _player->GetTargetField()->GetEnemy() ) );
	Fight(_playerCopy, _enemyCopy, false);
}



uint8_t Battlefield::CountNearObjects(Field *field)
{
	uint8_t summ = 0;
	for (direction dir = LEFT; dir <= DOWNRIGHT; dir = direction(dir + 1))
	{
		Field * nextField = GetNextField(field, dir);
		if (nextField != NULL &&
		( nextField->HaveEnemy() || nextField->HavePowerup() || nextField->HaveItem() ))
			++summ;
	}

	return summ;
}



void Battlefield::SetPlayer(Player * plr)
{
	_player = plr;
}


void Battlefield::SetDisplay(Display * dspl)
{
	_display = dspl;
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


bool Battlefield::BossIsDead() const
{
	return _boss->IsDead();
}



bool Battlefield::BossIsAlive() const
{
	return !_boss->IsDead();
}



// FOR TESTING

void Battlefield::TEST_Reveal()
{
	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			_field[row][column]->MakeVisible();
}
