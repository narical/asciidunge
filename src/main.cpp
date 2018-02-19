//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// main.cpp
//

#include <game.h>
#include <display.h>

int main()
{
	Display::NcursesInit();
	Game game;

	while (true) game.Run();

	Display::NcursesShutdown();
	return 0;
}

