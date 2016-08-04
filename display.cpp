/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * display.cpp
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */


#include "display.h"


Display::Display(Battlefield * btl, Player * plr) : m_battlefield(btl), m_player(plr), m_enemy(NULL)
{
	HORIZ_WALL = "";
	unsigned int wallSize = m_battlefield->GetSize() + 2;
	for (unsigned int i = 0; i < wallSize; ++i) HORIZ_WALL += "#";
}



void Display::DrawBattlefield()
{
	unsigned int bf_size = m_battlefield->GetSize();

	mvprintw(BF_ROW, BF_MARGIN, HORIZ_WALL.c_str());
	for (unsigned int rowIndex = 0; rowIndex < bf_size; ++rowIndex)
	{
		mvprintw(BF_ROW + rowIndex + 1, BF_MARGIN, "#");
		for (unsigned int colIndex = 0; colIndex < bf_size; ++colIndex) DrawField(rowIndex, colIndex);
		printw("#");
	}
	mvprintw(BF_ROW + bf_size + 1, BF_MARGIN, HORIZ_WALL.c_str());
}



void Display::DrawPlayerInfo()
{
	std::string name = m_player->GetName();
	int level = m_player->GetLevel();
	int damage = m_player->GetDamage();
	int HP = m_player->GetHP();
	int maxHP = m_player->GetMaxHP();
	int mana = m_player->GetMana();
	int maxMana = m_player->GetMaxMana();
	int exp = m_player->GetExp();
	int expMax = m_player->GetExpMax();

	std::string healthBar = ShowBar(HP, maxHP);
	std::string manaBar = ShowBar(mana, maxMana);
	std::string expBar = ShowBar(exp, expMax);

	mvprintw(PLAYER_ROW + 0, INFO_MARGIN, "Exp   %d / %d", exp, expMax);
	mvprintw(PLAYER_ROW + 1, INFO_MARGIN, "Mana  %d / %d", mana, maxMana);
	mvprintw(PLAYER_ROW + 5, INFO_MARGIN, "%s - level %d", name.c_str(), level);
	mvprintw(PLAYER_ROW + 7, INFO_MARGIN, " [+]  %d / %d", HP, maxHP);
	mvprintw(PLAYER_ROW + 9, INFO_MARGIN, " [*]    %d   ", damage);

	mvprintw(PLAYER_ROW + 0, BAR_MARGIN, "%s", expBar.c_str());
	mvprintw(PLAYER_ROW + 1, BAR_MARGIN, "%s", manaBar.c_str());
	mvprintw(PLAYER_ROW + 7, BAR_MARGIN, "%s", healthBar.c_str());
}



void Display::DrawEnemyInfo()
{
	Monster * targetEnemy = m_player->GetTarget()->GetEnemy();
	std::string name = targetEnemy->GetName();
	int level = targetEnemy->GetLevel();
	int damage = targetEnemy->GetDamage();
	int HP = targetEnemy->GetHP();
	int maxHP = targetEnemy->GetMaxHP();

	std::string healthBar = ShowBar(HP, maxHP);

	mvprintw(ENEMY_ROW + 0, INFO_MARGIN, "%s - level %d  ", name.c_str(), level);
	mvprintw(ENEMY_ROW + 2, INFO_MARGIN, " [+]   %d / %d", HP, maxHP);
	mvprintw(ENEMY_ROW + 4, INFO_MARGIN, " [*]     %d   ", damage);

	mvprintw(ENEMY_ROW + 2, BAR_MARGIN, "%s", healthBar.c_str());
}



char Display::DrawField(int rowIndex, int colIndex)
{
	Field *playerField = m_player->GetPosition();
	Field *field = m_battlefield->GetField(rowIndex, colIndex);

	if (field == playerField) printw("@");
	else if (!field->IsVisible()) printw(".");
	else
	{
		if (field->HaveEnemy())
	 	{
	 	 	if (field->GetEnemy()->GetLevel() == 10) printw("Z");
	 	 	else printw("%d", field->GetEnemy()->GetLevel());
	 	}
		else if (field != m_player->GetPosition() && field->HaveItem()) printw("*");
		else if (field == m_player->GetPosition() && field->HaveItem()) printw("@");
		else printw(" ");
	}
	return 0;
}



void Display::ShowCurrentFrame()
{
	clear();
	DrawBattlefield();
	DrawPlayerInfo();
	if (m_player->HaveTarget()) DrawEnemyInfo();
	refresh();
}



std::string Display::ShowBar(int current, int max) const
{
	int num;
	std::string result = "[";
	num = (current != 0 ? (int)( (double)current / max * BARWIDTH) : 0);
	for (int i = 0; i < num; ++i) result += '#';
	for (int i = 0; i < BARWIDTH - num; ++i) result += '.';
	result += ']';
	return result;
}



void Display::ShowVictoryScreen()
{
	clear();
	mvprintw(2,2,"Victory!");
	refresh();
}



void Display::ShowDefeatScreen()
{
	clear();
	mvprintw(2,2,"DEFEAT !");
	refresh();
}



void Display::NcursesInit()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
}



void Display::NcursesShutdown()
{
	clear();
	endwin();
}