//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// display.cpp
//


#include "headers/display.h"
#include "headers/input.h"
#include "headers/battlefield.h"
#include "headers/powerup.h"
#include "headers/player.h"
#include "headers/monster.h"
#include "headers/field.h"
#include <ncurses.h>

Display::Display(Battlefield * btl) :
_battlefield(btl),
_enemy(NULL),
_player(btl->GetPlayer()),
_frame(CURRENT)
{
	HORIZ_WALL = "";
	uint8_t wallSize = _battlefield->GetSize() + 2;
	for (uint8_t i = 0; i < wallSize; ++i) HORIZ_WALL += "#";
	for (eventtype event = LVLUP; event != EVENTS_END; event = eventtype(event + 1))
		_frameCounters[event] = 0;
	_player->SetDisplay(this);
	_battlefield->SetDisplay(this);
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



void Display::DrawBattlefield()
{
	uint8_t bf_size = _battlefield->GetSize();
	BoldOn();
	mvprintw(BF_ROW, BF_MARGIN, HORIZ_WALL.c_str());
	for (uint8_t rowIndex = 0; rowIndex < bf_size; ++rowIndex)
	{
		mvprintw(BF_ROW + rowIndex + 1, BF_MARGIN, "#");
		BoldOff();
		for (uint8_t colIndex = 0; colIndex < bf_size; ++colIndex) DrawField(rowIndex, colIndex);
		BoldOn();
		printw("#");
	}
	mvprintw(BF_ROW + bf_size + 1, BF_MARGIN, HORIZ_WALL.c_str());
	BoldOff();
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
	uint16_t damage = plr->GetDamage();
	uint16_t HP = plr->GetHP();
	uint16_t maxHP = plr->GetMaxHP();
	uint16_t mana = plr->GetMana();
	uint16_t maxMana = plr->GetMaxMana();
	uint16_t exp = plr->GetExp();
	uint16_t expMax = plr->GetExpMax();

	std::string healthBar = DrawBar(HP, maxHP);
	std::string manaBar = DrawBar(mana, maxMana);
	std::string expBar = DrawBar(exp, expMax);

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
		uint16_t damage = enemy->GetDamage();
		uint16_t HP = enemy->GetHP();
		uint16_t maxHP = enemy->GetMaxHP();

		std::string healthBar = DrawBar(HP, maxHP);

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
			if (field == playerTarget)
			{
				BoldOn();
				CheckEvent(MNSTR_HIT_1);
				CheckEvent(MNSTR_HIT_2);
				if (field->GetEnemy()->GetLevel() == 10) printw("Z");
				else printw("%d", field->GetEnemy()->GetLevel());
				EndCheck();
				BoldOff();
			}
			else
			{
				if (field->GetEnemy()->GetLevel() == 10) printw("Z");
				else printw("%d", field->GetEnemy()->GetLevel());
			}
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

		else if (field == playerField)
		{
			CheckEvent(LVLUP);
			CheckEvent(PLR_HIT_1);
			CheckEvent(PLR_HIT_2);
			printw("@");
			EndCheck();
		}

		else printw(" ");
	}
	return 0;
}



void Display::ReduceCounters()
{
	for (eventtype event = LVLUP; event != EVENTS_END; event = eventtype(event + 1))
		if (_frameCounters[event] > 0) --_frameCounters[event];
}



void Display::SwitchFrameType()
{
	_frame = (_frame == CURRENT ? FUTURE : CURRENT);
}



std::string Display::DrawBar(uint16_t current, uint16_t max) const
{
	uint16_t num;
	std::string result = "[";
	num = (current != 0 ? (uint16_t)( (double)current / max * BARWIDTH) : 0);
	for (uint16_t i = 0; i < num; ++i) result += '#';
	for (uint16_t i = 0; i < BARWIDTH - num; ++i) result += '.';
	result += ']';
	return result;
}



void Display::SendEvent(eventtype event)
{
	_frameCounters[event] = EVENT_TIMERS[event];
}



void Display::CheckEvent(eventtype event)
{
	switch (event)
	{
		case LVLUP:
		case HP_PWRUP:
		case MANA_PWRUP:
		case DMG_PWRUP:
			if (_frameCounters[event] > 0 && _frameCounters[event] % 2) BoldOn();
			break;
		case PLR_HIT_1:
		case MNSTR_HIT_1:
		case PLR_HIT_2:
		case MNSTR_HIT_2:
			if (_frameCounters[event] == 1) InvertOn();
			break;

		case EVENTS_END:;
	}
}



void Display::BoldOn()
{
	attron(A_BOLD);
}



void Display::BoldOff()
{
	attroff(A_BOLD);
}



void Display::InvertOn()
{
	attron(A_REVERSE);
}



void Display::EndCheck()
{
	attroff(A_BOLD);
	attroff(A_REVERSE);
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
