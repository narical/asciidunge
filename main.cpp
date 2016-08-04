/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2016 Joy Narical <jnarical@gmail.com>
 * 
 */
#include <ncurses.h>
#include "game.h"
#include "battlefield.h"
#include "player.h"
#include "display.h"

void ncurses_init();
void ncurses_off();


int main()
{
	Display::NcursesInit();
	Game game;

	while (true) game.Run();

	Display::NcursesShutdown();
	return 0;
}

