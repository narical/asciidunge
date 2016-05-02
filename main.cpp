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

void ncurses_init();
void ncurses_off();


int main()
{
	ncurses_init();
	
	Battlefield btl;
	Player plr;
	Game game;
	game.Run(&btl, &plr);
	ncurses_off();
	return 0;
}


inline void ncurses_init() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
}


inline void ncurses_off() {
	clear();
	endwin();
}
