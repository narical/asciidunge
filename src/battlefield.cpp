//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// battlefield.cpp
//

#include <battlefield.h>
#include <player.h>
#include <field.h>
#include <display.h>
#include <item.h>
#include <game.h>

#include <monsters/ghost.h>
#include <monsters/goblin.h>
#include <monsters/golem.h>
#include <monsters/mage.h>
#include <monsters/rogue.h>
#include <monsters/skeleton.h>
#include <monsters/troll.h>
#include <monsters/zombie.h>

Battlefield::Battlefield(Game *game) :
	_game(game), _boss(nullptr), _playerCopy(nullptr), _enemyCopy(nullptr)
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

	if (_playerCopy != nullptr) delete(_playerCopy);
	if (_enemyCopy != nullptr) delete(_enemyCopy);
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
	return nullptr;
}



void Battlefield::Fight(Player * player, Monster * enemy, bool realFight)
{
	Display *display = _game->GetDisplay();
	player->HandleItems("Sword of Readiness");
	
	uint16_t monsterInitiative = enemy->GetInitiative();
	uint16_t playerInitiative = player->GetInitiative();

	if (monsterInitiative >= playerInitiative)
	{
		enemy->Attack(player);
		if (realFight) display->SendEvent(PLR_HIT_1);

		if (player->IsAlive())
		{
			enemy->TakeDamage(player);
			if (realFight) display->SendEvent(MNSTR_HIT_2);
			
			if (enemy->IsDead())
			{
				if (realFight) player->GainExp(enemy);
				player->SetTargetField(nullptr);
			}
		}
	}
	else
	{
		enemy->TakeDamage(player);
		if (realFight) display->SendEvent(MNSTR_HIT_1);

		if (enemy->IsDead())
		{
			if (realFight) player->GainExp(enemy);
			player->SetTargetField(nullptr);
		}
		else
		{
			enemy->Attack(player);
			if (realFight) display->SendEvent(PLR_HIT_2);
		}
	}
	player->HandleItems("Sword of Readiness");
}



void Battlefield::CalculateNextFight()
{
	if (_playerCopy != 0) delete _playerCopy;
	if (_enemyCopy != 0) delete _enemyCopy;
//	_playerCopy = new Player( *_player );
	_playerCopy = new Player( *(_game->GetPlayer()) );
	_enemyCopy = new Monster( *( _game->GetPlayer()->GetTargetField()->GetEnemy() ) );
	Fight(_playerCopy, _enemyCopy, false);
}



uint8_t Battlefield::CountNearObjects(Field *field)
{
	uint8_t summ = 0;
	for (direction dir = LEFT; dir <= DOWNRIGHT; dir = direction(dir + 1))
	{
		Field * nextField = GetNextField(field, dir);
		if (nextField != nullptr &&
		( nextField->HaveEnemy() || nextField->HavePowerup() || nextField->HaveItem() ))
			++summ;
	}

	return summ;
}



// FOR TESTING

void Battlefield::TEST_Reveal()
{
	for (uint8_t row = 0; row < BF_SIZE; ++row)
		for (uint8_t column = 0; column < BF_SIZE; ++column)
			_field[row][column]->MakeVisible();
}
