/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * game.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "ncurses.h"
#include "game.h"
static const int BARWIDTH = 20;


Game::Game ()
{
  std::cout << "Game created!" << std::endl;
}


std::string Game::ShowBar(int current, int max) {
	int num;
	std::string result = "[";
	num = (current != 0 ? (int)( (double)current / max * BARWIDTH) : 0);
	for (int i = 0; i < num; ++i) result += '#';
	for (int i = 0; i < BARWIDTH - num; ++i) result += '.';
	result += ']';
	return result;
}


void Game::Run_RNG()
{
	srand( time(0) );
}


void Game::GetPlayerInput( Battlefield * btl, Player * plr)
{
	int input_key;
	input_key = getch();
	switch(input_key)
	{
		case 'r':
		case 'l':
		case 'u':
		case 'd':
			plr->Move(btl, input_key);
			break;
		case 'q':
			exit(0);
	}
}


// Главный игровой цикл
void Game::Run (Battlefield *btl, Player *plr) {

	while (true)
	{
		plr->LookAround(btl);
		clear();
		btl->Show ();
		plr->Show ();
		refresh();
		this->GetPlayerInput(btl, plr);
	}
}
