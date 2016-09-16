/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * display.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_
enum Frametype {CURRENT, FUTURE};
enum EventType {LVLUP, HP_PWRUP, MANA_PWRUP, DMG_PWRUP};

class Player;
class Battlefield;
class Monster;
class Field;
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>
#include "field.h"

class Display
{
	static const uint8_t BARWIDTH = 20;
	static const uint8_t BF_ROW = 1;
	static const uint8_t PLAYER_ROW = 1;
	static const uint8_t ENEMY_ROW = 14;
	static const uint8_t BF_MARGIN = 2;
	static const uint8_t INFO_MARGIN = 26;
	static const uint8_t BAR_MARGIN = 45;

	public:
		Display ( Battlefield * btl, Player * plr );
		void ShowFrame();
		void SendEvent(EventType);

		static void ShowVictoryScreen();
		static void ShowDefeatScreen();
		static void NcursesInit();
		static void NcursesShutdown();

	private:
		uint8_t m_levelUpCounter;
		uint8_t m_healthPowerupCounter;
		uint8_t m_manaPowerupCounter;
		uint8_t m_damagePowerupCounter;
				
		Battlefield * m_battlefield;
		Player * m_player;
		Monster * m_enemy;
		Frametype m_frame;
		std::string HORIZ_WALL;

		std::string ShowBar(uint8_t, uint8_t) const;
		void ReduceCounters();
		void SwitchFrameType();
		void CheckEvent(EventType);
		void EndCheck();
		void DrawBattlefield();
		void DrawPlayerInfo();
		void DrawEnemyInfo();
		char DrawField(uint8_t, uint8_t);
};

#endif // _DISPLAY_H_


	
