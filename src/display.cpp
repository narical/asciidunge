//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// display.cpp
//


#include <display.h>
#include <strings.h>
#include <input.h>
#include <battlefield.h>
#include <powerup.h>
#include <player.h>
#include <item.h>
#include <field.h>
#include <game.h>
#include <ncurses.h>

#include <monsters/ghost.h>
#include <monsters/goblin.h>
#include <monsters/golem.h>
#include <monsters/mage.h>
#include <monsters/rogue.h>
#include <monsters/skeleton.h>
#include <monsters/troll.h>
#include <monsters/zombie.h>

Display::Display(Game * game) :
_game(game),
_frame(CURRENT)
{
	HORIZ_WALL = "";
	uint8_t wallSize = BF_SIZE + 2;
	for (uint8_t i = 0; i < wallSize; ++i) HORIZ_WALL += "#";
	for (eventtype event = LVLUP; event != EVENTS_END; event = eventtype(event + 1))
		_frameCounters[event] = 0;
}



void Display::ShowFrame()
{
	clear();
	DrawBattlefield();
	DrawPlayerInfo();
	if (_game->GetPlayer()->HaveTarget()) DrawEnemyInfo();
	refresh();
	SwitchFrameType();
	ReduceCounters();
}



void Display::DrawBattlefield()
{
	BoldOn();
	mvprintw(BF_ROW, BF_MARGIN, HORIZ_WALL.c_str());
	for (uint8_t rowIndex = 0; rowIndex < BF_SIZE; ++rowIndex)
	{
		mvprintw(BF_ROW + rowIndex + 1, BF_MARGIN, "#");
		BoldOff();
		for (uint8_t colIndex = 0; colIndex < BF_SIZE; ++colIndex) DrawField(rowIndex, colIndex);
		BoldOn();
		printw("#");
	}
	mvprintw(BF_ROW + BF_SIZE + 1, BF_MARGIN, HORIZ_WALL.c_str());
	BoldOff();
}



void Display::DrawPlayerInfo()
{
	Player * plr_copy = nullptr;
	Player * plr = nullptr;
	Monster * enemy_copy = nullptr;
	
	plr = _game->GetPlayer();

	if (plr->HaveTarget())
	{
		plr_copy = _game->GetBattlefield()->GetPlayerCopy();
		enemy_copy = _game->GetBattlefield()->GetEnemyCopy();
	}

	Item *inv1 = plr->GetInventory(0);
	Item *inv2 = plr->GetInventory(1);
	Item *inv3 = plr->GetInventory(2);
	Item *inv4 = plr->GetInventory(3);
	Item *grnd = plr->GetPosition()->GetItem();
	Item *sel_item = plr->GetSelectedItem();

	if (plr_copy != nullptr && _frame == FUTURE)
		plr = plr_copy;
	else
		plr = _game->GetPlayer();

	std::string str_inv1 = (inv1 != nullptr ? "1. " + inv1->GetName() : "Empty slot");
	std::string str_inv2 = (inv2 != nullptr ? "2. " + inv2->GetName() : "Empty slot");
	std::string str_inv3 = (inv3 != nullptr ? "3. " + inv3->GetName() : "Empty slot");
	std::string str_inv4 = (inv4 != nullptr ? "4. " + inv4->GetName() : "Empty slot");
	std::string str_grnd = (grnd != nullptr ? GRND1 + grnd->GetName() + GRND2 : "");

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
	
	if (inv1 == sel_item && sel_item != nullptr)
	{
		BoldOn();
		str_inv1 += INV;
	}
		mvprintw(PLAYER_ROW + 3, INFO_MARGIN, "%s", str_inv1.c_str());
		BoldOff();
	
	if (inv2 == sel_item && sel_item != nullptr)
	{
		BoldOn();
		str_inv2 += INV;
	}
		mvprintw(PLAYER_ROW + 4, INFO_MARGIN, "%s", str_inv2.c_str());
		BoldOff();
	
	if (inv3 == sel_item && sel_item != nullptr)
	{
		BoldOn();
		str_inv3 += INV;
	}
		mvprintw(PLAYER_ROW + 5, INFO_MARGIN, "%s", str_inv3.c_str());
		BoldOff();
	
	if (inv4 == sel_item && sel_item != nullptr)
	{
		BoldOn();
		str_inv4 += INV;
	}
		mvprintw(PLAYER_ROW + 6, INFO_MARGIN, "%s", str_inv4.c_str());
		BoldOff();
	
	if (str_grnd != "")	mvprintw(PLAYER_ROW + 7, INFO_MARGIN, "%s", str_grnd.c_str());
	
	CheckEvent(LVLUP);
	mvprintw(PLAYER_ROW + 9, INFO_MARGIN, "%s - level %d", name.c_str(), level);
	EndCheck();
	CheckEvent(HP_PWRUP);
	mvprintw(PLAYER_ROW + 11, INFO_MARGIN, " [+]  %d / %d", HP, maxHP);
	EndCheck();
	CheckEvent(DMG_PWRUP);
	mvprintw(PLAYER_ROW + 13, INFO_MARGIN, " [*]    %d   ", damage);
	EndCheck();

	mvprintw(PLAYER_ROW + 0, BAR_MARGIN, "%s", expBar.c_str());
	mvprintw(PLAYER_ROW + 1, BAR_MARGIN, "%s", manaBar.c_str());
	mvprintw(PLAYER_ROW + 11, BAR_MARGIN, "%s", healthBar.c_str());

	if (plr_copy != nullptr)
	{
		std::string prediction;
		if (plr_copy->IsAlive() && enemy_copy->IsAlive()) prediction = "SAFE";
		else if (plr_copy->IsDead() && enemy_copy->IsAlive()) prediction = "DEATH !!!";
		else if (plr_copy->IsAlive() && enemy_copy->IsDead()) prediction = "Victory!";
		mvprintw(PLAYER_ROW + 13, BAR_MARGIN, "%s", prediction.c_str());
	}
}



void Display::DrawEnemyInfo()
{
	Monster * enemy = nullptr;
	if (_game->GetBattlefield()->GetEnemyCopy() != nullptr && _frame == FUTURE)
		enemy = _game->GetBattlefield()->GetEnemyCopy();
		
	else enemy = _game->GetPlayer()->GetTargetField()->GetEnemy();
	
	if (enemy != nullptr)
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
	Field *playerField = _game->GetPlayer()->GetPosition();
	Field *playerTarget = _game->GetPlayer()->GetTargetField();
	Field *field = _game->GetBattlefield()->GetField(rowIndex, colIndex);

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

		else if (field != playerField && field->HaveItem())
		{
			printw("i");
		}

		else if (field == playerField && field->HaveItem())
		{
			BoldOn();
			printw("@");
			BoldOff();
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
