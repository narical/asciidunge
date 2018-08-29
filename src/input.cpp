//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// input.cpp
//

#include "input.hpp"
#include "player.hpp"
#include "display.hpp"
#include "battlefield.hpp"
#include "game.hpp"
#include <libtcod.hpp>



Input::Input(Game * game) : _game(game)
{

}



void Input::GetPlayerInput()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
	switch(key.vk)
	{
		case TCODK_ESCAPE : exit(0); break;
		default:break;
	}


/*	Player *player = _game->GetPlayer();
	
	int input_key;
	input_key = getch();
	
	if (input_key) switch(input_key)
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
		case 'u':
			player->ActivateItem();
			break;
		case '1':
		case '2':
		case '3':
		case '4':
			player->SelectItem(input_key - '1');
			break;
		case 'r':
			_game->GetBattlefield()->TEST_Reveal();
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
	} */
}


void Input::WaitAnyKey()
{
	TCOD_key_t key;
	while( true )
	{
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
		if (key.vk == TCODK_NONE) continue;
		break;
	}
}

