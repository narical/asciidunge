/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * display.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "config.h"
#include <string>

class Battlefield;
class Player;
class Monster;

class Display
{
	public:
		Display (Battlefield * btl);
		void SendEvent(eventtype);
		void ShowFrame();

		static void ShowVictoryScreen();
		static void ShowDefeatScreen();
		static void NcursesShutdown();
		static void NcursesInit();

	private:
		uint16_t _levelUpCounter;
		uint16_t _healthPowerupCounter;
		uint16_t _manaPowerupCounter;
		uint16_t _damagePowerupCounter;
		std::string HORIZ_WALL;

		Battlefield * _battlefield;
		Monster * _enemy;
		Player * _player;
		frametype _frame;

		std::string DrawBar(uint16_t, uint16_t) const;
		char DrawField(uint8_t, uint8_t);
		void DrawBattlefield();
		void DrawPlayerInfo();
		void DrawEnemyInfo();
		void CheckEvent(eventtype);
		void SwitchFrameType();
		void ReduceCounters();
		void EndCheck();
		void BoldOff();
		void BoldOn();
};

#endif // _DISPLAY_H_

