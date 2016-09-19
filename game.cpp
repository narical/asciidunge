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
#include "input.h"



Game::Game ()
{
	Run_RNG();
}


void Game::Run ()
{
	_battlefield = new Battlefield();
	_player = new Player(_battlefield);
	Input *input = new Input(_battlefield);
	Display *display = new Display(_battlefield);

	while ( _player->IsAlive() && _battlefield->BossIsAlive() )
	{
		display->ShowFrame();
		input->GetPlayerInput();
	}

	CheckVictory() ? Victory() : Defeat();

	delete(_player);
	delete(_battlefield);
	delete(display);
	delete(input);
}



bool Game::CheckVictory()
{
	return (_player->IsAlive() && _battlefield->BossIsDead());
}


void Game::Victory()
{
	Display::ShowVictoryScreen();
	Input::WaitAnyKey();
}


void Game::Defeat()
{
	Display::ShowDefeatScreen();
	Input::WaitAnyKey();
}


void Game::Run_RNG()
{
	srand( time(0) );
}
