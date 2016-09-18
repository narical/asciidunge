/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2016 Joy Narical <jnarical@gmail.com>
 * 
 */
void ncurses_init();
void ncurses_off();

#include <ncurses.h>
#include "game.h"
#include "display.h"

int main()
{
	Display::NcursesInit();
	Game game;

	while (true) game.Run();

	Display::NcursesShutdown();
	return 0;
}

