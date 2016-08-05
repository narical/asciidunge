/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * display.cpp
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */


#include "display.h"


Display::Display(Battlefield * btl, Player * plr) :
m_levelUpCounter(0),
m_battlefield(btl),
m_player(plr),
m_enemy(NULL)
{
	HORIZ_WALL = "";
	unsigned int wallSize = m_battlefield->GetSize() + 2;
	for (unsigned int i = 0; i < wallSize; ++i) HORIZ_WALL += "#";
	m_player->SetDisplay(this);
}



void Display::DrawBattlefield()
{
	unsigned int bf_size = m_battlefield->GetSize();
	attron(A_BOLD);
	mvprintw(BF_ROW, BF_MARGIN, HORIZ_WALL.c_str());
	for (unsigned int rowIndex = 0; rowIndex < bf_size; ++rowIndex)
	{
		mvprintw(BF_ROW + rowIndex + 1, BF_MARGIN, "#");
		attroff(A_BOLD);
		for (unsigned int colIndex = 0; colIndex < bf_size; ++colIndex) DrawField(rowIndex, colIndex);
		attron(A_BOLD);
		printw("#");
	}
	mvprintw(BF_ROW + bf_size + 1, BF_MARGIN, HORIZ_WALL.c_str());
	attroff(A_BOLD);
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
	CheckEvent(LVLUP);
	mvprintw(PLAYER_ROW + 5, INFO_MARGIN, "%s - level %d", name.c_str(), level);
	EndCheck();
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
	Field *playerTarget = m_player->GetTarget();

	if (!field->IsVisible()) printw(".");
	else
	{
		if (field->HaveEnemy())
	 	{
			if (field == playerTarget) attron(A_BOLD);
	 	 	if (field->GetEnemy()->GetLevel() == 10) printw("Z");
	 	 	else printw("%d", field->GetEnemy()->GetLevel());
			attroff(A_BOLD);
	 	}
		else if (field != playerField && field->HaveItem()) printw("*");
		else if (field == playerField && !field->HaveItem())
		{
			CheckEvent(LVLUP);
			printw("@");
			EndCheck();
		}
		else if (field == m_player->GetPosition() && field->HaveItem())
		{
			attron(A_BOLD);
			printw("@");
			attroff(A_BOLD);
		}
		else printw(" ");
	}
	return 0;
}



void Display::ShowFrame()
{
	clear();
	DrawBattlefield();
	DrawPlayerInfo();
	if (m_player->HaveTarget()) DrawEnemyInfo();
	refresh();
	ReduceCounters();
}



void Display::ReduceCounters()
{
	if (m_levelUpCounter > 0) --m_levelUpCounter; 
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



void Display::SendEvent(EventType event)
{
	switch (event)
	{
		case LVLUP:
			m_levelUpCounter = 6;
			break;
		
	}
}



void Display::CheckEvent(EventType event)
{
	switch (event)
	{
		case LVLUP:
			if (m_levelUpCounter > 0 && m_levelUpCounter % 2) attron(A_BOLD);
			break;
		
	}
}



void Display::EndCheck()
{
	attroff(A_BOLD);
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
	halfdelay(5);
}



void Display::NcursesShutdown()
{
	clear();
	endwin();
}
