//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// display.h
//

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "config.hpp"
#include <string>

class Game;

class Display
{
	public:
		explicit Display (Game *);
		void SendEvent(eventtype);
		void ShowFrame();

		static void ShowVictoryScreen();
		static void ShowDefeatScreen();
		static void NcursesShutdown();
		static void NcursesInit();

	private:
		uint8_t _frameCounters[4];
		std::string HORIZ_WALL;
		Game *_game;
		frametype _frame;


		std::string DrawBar(uint16_t, uint16_t) const;
		char DrawField(uint8_t, uint8_t);
		void CheckEvent(eventtype);
		void DrawBattlefield();
		void SwitchFrameType();
		void DrawPlayerInfo();
		void ReduceCounters();
		void DrawEnemyInfo();
		void EndCheck();
		void InvertOn();
		void BoldOff();
		void BoldOn();
};

#endif // _DISPLAY_H_

