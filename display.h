/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * display.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

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
#include "field.h"

class Display
{
	static const unsigned int BARWIDTH = 20;
	static const unsigned int BF_ROW = 1;
	static const unsigned int PLAYER_ROW = 1;
	static const unsigned int ENEMY_ROW = 14;
	static const unsigned int BF_MARGIN = 2;
	static const unsigned int INFO_MARGIN = 26;
	static const unsigned int BAR_MARGIN = 45;

	public:
		Display ( Battlefield * btl, Player * plr );
		void ShowCurrentFrame();
		static void ShowVictoryScreen();
		static void ShowDefeatScreen();
		static void NcursesInit();
		static void NcursesShutdown();


	private:
		void ClearFrames();
		void DrawBattlefield();
		void DrawPlayerInfo();
		void DrawEnemyInfo();
		char DrawField(int, int);
		std::string HORIZ_WALL;
		std::string ShowBar(int, int) const;

		Battlefield * m_battlefield;
		Player * m_player;
		Monster * m_enemy;
};

#endif // _DISPLAY_H_


	
