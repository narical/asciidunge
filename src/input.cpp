//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// input.cpp
//

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
		case 't':
			player->TakeItem();
			break;
		case 'd':
			player->DropItem();
			break;			
		case '1':
		case '2':
		case '3':		
		case '4':		
			player->SelectItem(input_key - '1');
			break;
		case 'r':
			_battlefield->TEST_Reveal();
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

