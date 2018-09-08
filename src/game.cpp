//
// Copyright (c) 2018 Joy Narical <jnarical@gmail.com> MIT license
//
// game.cpp
//

#include "game.hpp"
//#include <cassert>
#include <libtcod.hpp>


Game::Game() {

    TCODSystem::setFps(MAX_FPS);
    TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE.c_str(), false);
    m_data->player_x = SCREEN_WIDTH / 2;
    m_data->player_y = SCREEN_HEIGHT / 2;
    m_data->player_char = '@';
    this->run();
}



void Game::run() {

	while (!TCODConsole::isWindowClosed()) {
        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
        switch(key.vk) {
            case TCODK_UP: m_data->player_y--; break;
            case TCODK_DOWN: m_data->player_y++; break;
            case TCODK_LEFT: m_data->player_x--; break;
            case TCODK_RIGHT: m_data->player_x++; break;
            case TCODK_ESCAPE: exit(EXIT_SUCCESS);
            default: break;
        }
	    TCODConsole::root->clear();
        TCODConsole::root->putChar(
            m_data->player_x, m_data->player_y, m_data->player_char);
	    TCODConsole::flush();
	}
}



Game::~Game() {

}
