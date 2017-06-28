//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// game.h
//

#ifndef _GAME_H_
#define _GAME_H_

class Battlefield;
class Display;
class Player;
class Input;



class Game
{
	public:
		Game();
		~Game();
		void Run();
		bool CheckVictory();
		void Victory();
		void Defeat();
		static void Run_RNG();

		Battlefield *GetBattlefield() { return _battlefield; }
		Display *GetDisplay() { return _display; }
		Player *GetPlayer() { return _player; }
		Input *GetInput() { return _input; }

	private:
		Battlefield *_battlefield;
		Display *_display;
		Player *_player;
		Input *_input;
};

#endif // _GAME_H_

