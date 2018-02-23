//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// main.cpp
//

#include "game.hpp"
#include "display.hpp"

int main()
{
	Display::NcursesInit();
	Game game;

	while (true) game.Run();

	Display::NcursesShutdown();
	return 0;
}

