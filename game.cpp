/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * game.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "ncurses.h"
#include "game.h"


Game::Game ()
{ }


void Game::Run ()   //TODO: move all input to Input class
{
	Run_RNG();

	Battlefield *btl = new Battlefield();
	Player *plr = new Player(btl);
	Display *display = new Display(btl, plr);

	while ( plr->IsAlive() )
	{
		plr->LookAround();
		display->ShowFrame();
		GetPlayerInput(plr);
	 	if (CheckVictory()) break;
	}
	CheckVictory() ? Victory() : Defeat();

	delete(plr);
	delete(btl);
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
	return !Monster::s_Quantity;
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
