/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * display.cpp
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */


#include "display.h"


Display::Display(Battlefield * btl, Player * plr) :
_levelUpCounter(0),
_healthPowerupCounter(0),
_manaPowerupCounter(0),
_damagePowerupCounter(0),
_battlefield(btl),
_player(plr),
_enemy(NULL),
_frame(CURRENT)
{
	HORIZ_WALL = "";
	uint8_t wallSize = _battlefield->GetSize() + 2;
	for (uint8_t i = 0; i < wallSize; ++i) HORIZ_WALL += "#";
	_player->SetDisplay(this);
}



void Display::DrawBattlefield()
{
	uint8_t bf_size = _battlefield->GetSize();
	attron(A_BOLD);
	mvprintw(BF_ROW, BF_MARGIN, HORIZ_WALL.c_str());
	for (uint8_t rowIndex = 0; rowIndex < bf_size; ++rowIndex)
	{
		mvprintw(BF_ROW + rowIndex + 1, BF_MARGIN, "#");
		attroff(A_BOLD);
		for (uint8_t colIndex = 0; colIndex < bf_size; ++colIndex) DrawField(rowIndex, colIndex);
		attron(A_BOLD);
		printw("#");
	}
	mvprintw(BF_ROW + bf_size + 1, BF_MARGIN, HORIZ_WALL.c_str());
	attroff(A_BOLD);
}



void Display::DrawPlayerInfo()
{
	Player * plr_copy = NULL;
	Player * plr = NULL;
	Monster * enemy_copy = NULL;

	if (_player->HaveTarget())
	{
		plr_copy = _battlefield->GetPlayerCopy();
		enemy_copy = _battlefield->GetEnemyCopy();
	}

	if (plr_copy != NULL && _frame == FUTURE)
		plr = plr_copy;
	else
		plr = _player;
		 
	std::string name = plr->GetName();
	uint8_t level = plr->GetLevel();
	uint8_t damage = plr->GetDamage();
	uint8_t HP = plr->GetHP();
	uint8_t maxHP = plr->GetMaxHP();
	uint8_t mana = plr->GetMana();
	uint8_t maxMana = plr->GetMaxMana();
	uint16_t exp = plr->GetExp();
	uint16_t expMax = plr->GetExpMax();

	std::string healthBar = ShowBar(HP, maxHP);
	std::string manaBar = ShowBar(mana, maxMana);
	std::string expBar = ShowBar(exp, expMax);

	mvprintw(PLAYER_ROW + 0, INFO_MARGIN, "Exp   %u / %u", exp, expMax);
	CheckEvent(MANA_PWRUP);
	mvprintw(PLAYER_ROW + 1, INFO_MARGIN, "Mana  %u / %u", mana, maxMana);
	EndCheck();
	CheckEvent(LVLUP);
	mvprintw(PLAYER_ROW + 5, INFO_MARGIN, "%s - level %d", name.c_str(), level);
	EndCheck();
	CheckEvent(HP_PWRUP);
	mvprintw(PLAYER_ROW + 7, INFO_MARGIN, " [+]  %d / %d", HP, maxHP);
	EndCheck();
	CheckEvent(DMG_PWRUP);
	mvprintw(PLAYER_ROW + 9, INFO_MARGIN, " [*]    %d   ", damage);
	EndCheck();

	mvprintw(PLAYER_ROW + 0, BAR_MARGIN, "%s", expBar.c_str());
	mvprintw(PLAYER_ROW + 1, BAR_MARGIN, "%s", manaBar.c_str());
	mvprintw(PLAYER_ROW + 7, BAR_MARGIN, "%s", healthBar.c_str());

	if (plr_copy != NULL)
	{
		std::string prediction;
		if (plr_copy->IsAlive() && enemy_copy->IsAlive()) prediction = "SAFE";
		else if (plr_copy->IsDead() && enemy_copy->IsAlive()) prediction = "DEATH !!!";
		else if (plr_copy->IsAlive() && enemy_copy->IsDead()) prediction = "Victory!";
		mvprintw(PLAYER_ROW + 9, BAR_MARGIN, "%s", prediction.c_str());
	}
}



void Display::DrawEnemyInfo()
{
	Monster * enemy = NULL;
	if (_battlefield->GetEnemyCopy() != NULL && _frame == FUTURE) enemy = _battlefield->GetEnemyCopy();
	else enemy = _player->GetTargetField()->GetEnemy();
	
	if (enemy != NULL)
	{
		std::string name = enemy->GetName();
		uint8_t level = enemy->GetLevel();
		uint8_t damage = enemy->GetDamage();
		uint8_t HP = enemy->GetHP();
		uint8_t maxHP = enemy->GetMaxHP();

		std::string healthBar = ShowBar(HP, maxHP);

		mvprintw(ENEMY_ROW + 0, INFO_MARGIN, "%s - level %d  ", name.c_str(), level);
		mvprintw(ENEMY_ROW + 2, INFO_MARGIN, " [+]   %d / %d", HP, maxHP);
		mvprintw(ENEMY_ROW + 4, INFO_MARGIN, " [*]     %d   ", damage);

		mvprintw(ENEMY_ROW + 2, BAR_MARGIN, "%s", healthBar.c_str());
	}
}



char Display::DrawField(uint8_t rowIndex, uint8_t colIndex)
{
	Field *playerField = _player->GetPosition();
	Field *field = _battlefield->GetField(rowIndex, colIndex);
	Field *playerTarget = _player->GetTargetField();

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
	 	else if (field != playerField && field->HavePowerup())
	 		{
	 			switch (field->GetPowerup()->GetType())
	 			{
	 				case HEALTH:
	 					printw("+");
	 					break;
	 					
	 				case MANA:
	 					printw("x");
	 					break;
	 					
	 				case DAMAGE:
	 					printw("*");
	 			}
	 		}
	 	else if (field == playerField && field->HavePowerup())
		{
			attron(A_BOLD);
			printw("@");
			attroff(A_BOLD);
		}	 	

		else if (field == playerField)
		{
			CheckEvent(LVLUP);
			printw("@");
			EndCheck();
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
	if (_player->HaveTarget()) DrawEnemyInfo();
	refresh();
	SwitchFrameType();
	ReduceCounters();
}



void Display::ReduceCounters()
{
	if (_levelUpCounter > 0) --_levelUpCounter;
	if (_healthPowerupCounter > 0) --_healthPowerupCounter;
	if (_manaPowerupCounter > 0) --_manaPowerupCounter;
	if (_damagePowerupCounter > 0) --_damagePowerupCounter;
}


void Display::SwitchFrameType()
{
	_frame = (_frame == CURRENT ? FUTURE : CURRENT);
}


std::string Display::ShowBar(uint8_t current, uint8_t max) const
{
	uint8_t num;
	std::string result = "[";
	num = (current != 0 ? (uint8_t)( (double)current / max * BARWIDTH) : 0);
	for (uint8_t i = 0; i < num; ++i) result += '#';
	for (uint8_t i = 0; i < BARWIDTH - num; ++i) result += '.';
	result += ']';
	return result;
}



void Display::SendEvent(EventType event)
{
	switch (event)
	{
		case LVLUP:
			_levelUpCounter = 6;
			break;
			
		case HP_PWRUP:
			_healthPowerupCounter = 6;
			break;
			
		case MANA_PWRUP:
			_manaPowerupCounter = 6;
			break;
			
		case DMG_PWRUP:
			_damagePowerupCounter = 6;
	}
}



void Display::CheckEvent(EventType event)
{
	switch (event)
	{
		case LVLUP:
			if (_levelUpCounter > 0 && _levelUpCounter % 2) attron(A_BOLD);
			break;
			
		case HP_PWRUP:
			if (_healthPowerupCounter > 0 && _healthPowerupCounter % 2) attron(A_BOLD);
			break;
			
		case MANA_PWRUP:
			if (_manaPowerupCounter > 0 && _manaPowerupCounter % 2) attron(A_BOLD);
			break;
			
		case DMG_PWRUP:
			if (_damagePowerupCounter > 0 && _damagePowerupCounter % 2) attron(A_BOLD);
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
