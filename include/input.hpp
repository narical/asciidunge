//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// input.h
//

#ifndef _INPUT_H_
#define _INPUT_H_

class Game;


class Input
{
	public:
		explicit Input(Game *);
		void GetPlayerInput();
		static void WaitAnyKey();

	private:
		Game * _game;

};

#endif // _INPUT_H_
