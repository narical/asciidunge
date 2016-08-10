/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * game.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _GAME_H_
#define _GAME_H_

class Battlefield;
class Player;
class Display;
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include "battlefield.h"
#include "player.h"
#include "display.h"

class Game
{
	public:
		Game ();
		void Run();
		void GetPlayerInput(Player *);
		bool CheckVictory();
		void Victory();
		void Defeat();
		static void Run_RNG();
};

#endif // _GAME_H_

