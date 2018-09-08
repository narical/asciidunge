//
// Copyright (c) 2018 Joy Narical <jnarical@gmail.com> MIT license
//
// game.h
//

#ifndef _GAME_H_
#define _GAME_H_
#include "config.hpp"
#include <memory>


struct GameData {
    int player_x;
    int player_y;
    int player_char;
};

typedef std::shared_ptr<GameData> GameDataRef;


class Game
{
	public:
		explicit Game();
		~Game();
        void run();

	private:
        GameDataRef m_data = std::make_shared<GameData>();
};

#endif // _GAME_H_
