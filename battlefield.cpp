/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * battlefield.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */
class Game;
#include <cstdlib>
#include "battlefield.h"
#include "game.h"


Battlefield::Battlefield() {
	Game::Run_RNG();
	int maxEnemyCount = rand() % 11 + 5;
	int maxItemsCount = rand() % 3 + 3;

	for (int i = 0; i < 20; ++i)
		for (int j = 0; j < 20; ++j)
			this->field[i][j] = new Field;

	for (int i = 0; i < maxEnemyCount; ++i)
	{
		int row = rand() % 20;
		int col = rand() % 20;
		this->field[row][col]->SpawnEnemy();
	}

	for (int i = 0; i < maxItemsCount; ++i)
	{
		int row = rand() % 20;
		int col = rand() % 20;
		this->field[row][col]->SpawnItem();
	}
}


Field * Battlefield::GetField(int x, int y)
{
	return this->field[x][y];
}


// Отображение игрового поля
void Battlefield::Show ()
{
	printw ("######################\n");
	for (int i = 0; i < 20; ++i) {
		printw ("#");
		for (int j = 0; j < 20; ++j)
			this->field[i][j]->Show();
		printw ("#\n");
	}
	printw ("######################\n");
//TODO: сделать размер игрового поля константой
}
