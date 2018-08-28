//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// main.cpp
//

#include "game.hpp"
#include "display.hpp"
#include <libtcod.hpp>

int main()
{
	TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
	Display::NcursesInit();
	Game game;
	while (true) game.Run();

	Display::NcursesShutdown();
	return 0;
}

