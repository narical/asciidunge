/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * input.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "headers/input.h"
#include "headers/battlefield.h"
#include "headers/player.h"
#include "headers/display.h"
#include <ncurses.h>



Input::Input(Battlefield * btl) : _battlefield(btl)
{

}



void Input::GetPlayerInput()
{
	Player *player = _battlefield->GetPlayer();
	int input_key;
	input_key = getch();
	switch(input_key)
	{
		case KEY_RIGHT:
		case KEY_LEFT:
		case KEY_UP:
		case KEY_DOWN:
			player->Act(input_key);
			break;
		case 'l':
			player->TEST_LevelUp();
			break;
		case 'h':
			player->Heal();
			break;
		case 'q':
			Display::NcursesShutdown();
			exit(0);
	}
}


void Input::WaitAnyKey()
{
	while (true) if (getch() != ERR) break;
}

