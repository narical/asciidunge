/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * game.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _GAME_H_
#define _GAME_H_

class Player;
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "battlefield.h"
#include "player.h"

class Game {
public:
	Game ();
	void Run (Battlefield *, Player *);
	static std::string ShowBar (int, int);
	static void Run_RNG();
};

#endif // _GAME_H_

