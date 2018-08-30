//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// input.cpp
//

#include "input.hpp"
#include "config.hpp"
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
	Player *player = _game->GetPlayer();
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
	switch( key.vk )
	{
		case TCODK_UP	 :	player->Act(UP);	break;
		case TCODK_RIGHT :	player->Act(RIGHT);	break;
		case TCODK_DOWN	 :	player->Act(DOWN);	break;
		case TCODK_LEFT	 :	player->Act(LEFT);	break;
		case TCODK_1	 :	player->SelectItem(1);	break;
		case TCODK_2 	 :	player->SelectItem(2);	break;
		case TCODK_3 	 :	player->SelectItem(3);	break;
		case TCODK_4 	 :	player->SelectItem(4);	break;
		case TCODK_ESCAPE:	exit(0);		break;
		case TCODK_CHAR	 :	switch( key.c )
		{
			case 't':
				player->TakeItem();
				break;
			case 'd':
				player->DropItem();
				break;
			case 'u':
				player->ActivateItem();
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
				exit(0);
				break;

			default: break;
		}; break;
		default: break;
	}
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

