//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// game.cpp
//

#include "game.hpp"
#include "battlefield.hpp"
#include "player.hpp"
#include "display.hpp"
#include "input.hpp"
#include <ctime>
#include <cassert>



Game::Game() :
		_battlefield(nullptr),
		_display(nullptr),
		_player(nullptr),
		_input(nullptr)
{
	Run_RNG();
	_input = new Input(this);
	_display = new Display(this);
}



Game::~Game()
{
	delete(_input);
	delete(_display);
	if (_battlefield != nullptr) delete(_battlefield);
	if (_player !=nullptr) delete(_player);
}


void Game::Run ()
{
	// if (_battlefield != nullptr) delete(_battlefield);
	_battlefield = new Battlefield(this); //FIX: memory leak

	if (_player !=nullptr) delete(_player);
	_player = new Player(this);


	while ( _player->IsAlive() && _battlefield->BossIsAlive() )
	{
		_display->ShowFrame();
		_input->GetPlayerInput();
	}

	CheckVictory() ? Victory() : Defeat();

	delete(_player);
	delete(_battlefield);
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
