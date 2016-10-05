//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// game.h
//

#ifndef _GAME_H_
#define _GAME_H_

class Battlefield;
class Player;



class Game
{
	public:
		Game ();
		void Run();
		bool CheckVictory();
		void Victory();
		void Defeat();
		static void Run_RNG();

	private:
		Battlefield *_battlefield;
		Player *_player;
};

#endif // _GAME_H_

