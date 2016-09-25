//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// game.cpp
//

#include "headers/game.h"
#include "headers/battlefield.h"
#include "headers/player.h"
#include "headers/display.h"
#include "headers/input.h"
#include <ctime>



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
