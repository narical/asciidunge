/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * game.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "game.h"
//#include <cstdlib>
#include <ctime>
#include "battlefield.h"
#include "player.h"
#include "display.h"
#include "ncurses.h"



Game::Game ()
{ }


void Game::Run ()   //TODO: move all input to Input class
{
	Run_RNG();

	_battlefield = new Battlefield();
	_player = new Player(_battlefield);

	Display *display = new Display(_battlefield, _player);

	while ( _player->IsAlive() && _battlefield->BossIsAlive() )
	{
		display->ShowFrame();
		GetPlayerInput(_player);
	}
	CheckVictory() ? Victory() : Defeat();

	delete(_player);
	delete(_battlefield);
	delete(display);
}


void Game::GetPlayerInput(Player * plr) //TODO: move all input to Input class
{
	int input_key;
	input_key = getch();
	switch(input_key)
	{
		case KEY_RIGHT:
		case KEY_LEFT:
		case KEY_UP:
		case KEY_DOWN:
			plr->Act(input_key);
			break;
		case 'l':
			plr->TEST_LevelUp();
			break;
		case 'h':
			plr->Heal();
			break;
		case 'q':
			Display::NcursesShutdown();
			exit(0);
	}
}


bool Game::CheckVictory()
{
	return (_player->IsAlive() && _battlefield->BossIsDead());
}


void Game::Victory()
{
	Display::ShowVictoryScreen();
	while (true)
	{
		if (getch() != ERR) break;
	}
}


void Game::Defeat()
{
	Display::ShowDefeatScreen();
	while (true)
	{
		if (getch() != ERR) break;
	}
}


void Game::Run_RNG()
{
	srand( time(0) );
}
