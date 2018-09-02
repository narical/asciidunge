//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// display.cpp
//


#include "display.hpp"
#include "strings.hpp"
#include "input.hpp"
#include "battlefield.hpp"
#include "powerup.hpp"
#include "player.hpp"
#include "item.hpp"
#include "monster.hpp"
#include "field.hpp"
#include "game.hpp"
#include <libtcod.hpp>
#include <cassert>
#include <iostream>

//horizontal wall
//std::string Display::HORIZ_WALL = "######################";
std::string Display::HORIZ_WALL = "";

Display::Display(Game * game) :
_game(game),
_frame(Frames::CURRENT)
{
    TCODSystem::setFps(MAX_FPS);
    TCODConsole::setCustomFont("courier12x12_aa_tc.png",TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::initRoot(SCREEN_WIDTH,SCREEN_HEIGHT,GAME_TITLE.c_str(),false);
    TCOD_renderer_t ren = TCODSystem::getRenderer();
    if (ren == TCOD_RENDERER_SDL) std::cout << "SDL" << std::endl;
    
    TCODConsole::credits();
    TCODConsole::root->setDefaultBackground(TCODColor::black);
    TCODConsole::root->setDefaultForeground(TCODColor::red);

    for (uint8_t i=0; i<BF_SIZE+2; ++i) HORIZ_WALL+="#";

	// Make frame counters to zero for every event type
	uint8_t list_begin = static_cast<uint8_t>(Events::LVLUP);
	uint8_t list_end = static_cast<uint8_t>(Events::EVENTS_END);
	for (uint8_t event = list_begin; event < list_end; ++event)	_frameCounters[event] = 0;
}



void Display::ShowFrame()
{
    TCODConsole::root->clear();
	DrawBattlefield();
	DrawPlayerInfo();
	if (_game->GetPlayer()->HaveTarget()) DrawEnemyInfo();
    TCODConsole::flush();
}



void Display::DrawBattlefield()
{
    TCODConsole::root->print(BF_MARGIN, BF_ROW, HORIZ_WALL.c_str());
	for (uint8_t rowIndex = 1; rowIndex <= BF_SIZE; ++rowIndex)
	{
		TCODConsole::root->print(BF_MARGIN, BF_ROW + rowIndex, "#\n");
		for (uint8_t colIndex = 1; colIndex <= BF_SIZE; ++colIndex) 
    		TCODConsole::root->print(BF_MARGIN + colIndex, BF_ROW + rowIndex, DrawField(rowIndex-1, colIndex-1));
		TCODConsole::root->print(BF_MARGIN + BF_SIZE + 1, BF_ROW + rowIndex, "#\n");
	}
    TCODConsole::root->print(BF_MARGIN, BF_ROW + BF_SIZE + 1, HORIZ_WALL.c_str());
}



void Display::DrawPlayerInfo()
{
	Player * plr_copy = nullptr;
	Monster * enemy_copy = nullptr;
	
	Player * plr = _game->GetPlayer();

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

	if (plr_copy != nullptr && _frame == Frames::FUTURE)
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

    std::string exp_line = "Exp  "+std::to_string(exp)+" / "+std::to_string(expMax);
    TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 0, exp_line.c_str());
	//CheckEvent(MANA_PWRUP);
    std::string mana_line = "Mana  "+std::to_string(mana)+" / "+std::to_string(maxMana);
    TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 1, mana_line.c_str());
	//EndCheck();
	
	if (inv1 == sel_item && sel_item != nullptr)
	{
		//BoldOn();
		str_inv1 += INV;
	}
		TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 3, str_inv1.c_str());
		//BoldOff();
	
	if (inv2 == sel_item && sel_item != nullptr)
	{
		//BoldOn();
		str_inv2 += INV;
	}
		TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 4, str_inv2.c_str());
		//BoldOff();
	
	if (inv3 == sel_item && sel_item != nullptr)
	{
		//BoldOn();
		str_inv3 += INV;
	}
		TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 5, str_inv3.c_str());
		//BoldOff();
	
	if (inv4 == sel_item && sel_item != nullptr)
	{
		//BoldOn();
		str_inv4 += INV;
	}
		TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 6, str_inv4.c_str());
		//BoldOff();
	
	if (str_grnd != "")	TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 7, str_grnd.c_str());
	
	//CheckEvent(Events::LVLUP);
	std::string level_line = name + " - level " + std::to_string(level);
	TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 9, level_line.c_str());
	//EndCheck();
	//CheckEvent(HP_PWRUP);
	std::string health_line = " [+]  " + std::to_string(HP) + " / " + std::to_string(maxHP);
	TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 11, health_line.c_str());
	//EndCheck();
	//CheckEvent(DMG_PWRUP);
	std::string damage_line = " [*]    " + std::to_string(damage);
	TCODConsole::root->print(INFO_MARGIN, PLAYER_ROW + 13, damage_line.c_str());
	//EndCheck();

	TCODConsole::root->print(BAR_MARGIN, PLAYER_ROW + 0, expBar.c_str());
	TCODConsole::root->print(BAR_MARGIN, PLAYER_ROW + 1, manaBar.c_str());
	TCODConsole::root->print(BAR_MARGIN, PLAYER_ROW + 11, healthBar.c_str());

	if (plr_copy != nullptr)
	{
		std::string prediction;
		if (plr_copy->IsAlive() && enemy_copy->IsAlive()) prediction = "SAFE";
		else if (plr_copy->IsDead() && enemy_copy->IsAlive()) prediction = "DEATH !!!";
		else if (plr_copy->IsAlive() && enemy_copy->IsDead()) prediction = "Victory!";
		TCODConsole::root->print(BAR_MARGIN, PLAYER_ROW + 13, prediction.c_str());
	}
}



void Display::DrawEnemyInfo()
{
/*	Monster * enemy = nullptr;
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

		TCODConsole::root->print(ENEMY_ROW + 0, INFO_MARGIN, "%s - level %d  ", name.c_str(), level);
		TCODConsole::root->print(ENEMY_ROW + 2, INFO_MARGIN, " [+]   %d / %d", HP, maxHP);
		TCODConsole::root->print(ENEMY_ROW + 4, INFO_MARGIN, " [*]     %d   ", damage);

		TCODConsole::root->print(ENEMY_ROW + 2, BAR_MARGIN, "%s", healthBar.c_str());
	} */
}



const char* Display::DrawField(uint8_t rowIndex, uint8_t colIndex) const
{
	Field *playerField = _game->GetPlayer()->GetPosition();
	Field *playerTarget = _game->GetPlayer()->GetTargetField();
	Field *field = _game->GetBattlefield()->GetField(rowIndex, colIndex);
    assert(field != nullptr);

	if (!field->IsVisible()) return ".\n";
	else
	{
		if (field->HaveEnemy())
	 	{
			if (field == playerTarget)
			{
				//BoldOn();
				//CheckEvent(MNSTR_HIT_1);
				//CheckEvent(MNSTR_HIT_2);
				if (field->GetEnemy()->GetLevel() == 10) return "Z\n";
				else return (std::to_string(field->GetEnemy()->GetLevel()) + "\n").c_str();
				//EndCheck();
				//BoldOff();
			}
			else
			{
				if (field->GetEnemy()->GetLevel() == 10) return "Z\n";
				else return (std::to_string(field->GetEnemy()->GetLevel()) + "\n").c_str();
			}
		}

		else if (field != playerField && field->HavePowerup())
		{
			switch (field->GetPowerup()->GetType())
			{
				case Powerups::HEALTH:
					return "+\n";
					break;
					
				case Powerups::MANA:
					return "x\n";
					break;
					
				case Powerups::DAMAGE:
					return "*\n";
			}
		}

		else if (field != playerField && field->HaveItem())
		{
			return "i\n";
		}

		else if (field == playerField && field->HaveItem())
		{
			// BoldOn();
			return "@\n";
			// BoldOff();
		}

		else if (field == playerField)
		{
			// CheckEvent(Events::LVLUP);
			// CheckEvent(PLR_HIT_1);
			// CheckEvent(PLR_HIT_2);
			return "@\n";
			// EndCheck();
		}

		else return " \n";
	}
    return "S\n";
}



void Display::ReduceCounters()
{
	uint8_t list_begin = static_cast<uint8_t>(Events::LVLUP);
	uint8_t list_end = static_cast<uint8_t>(Events::EVENTS_END);
	
	for (uint8_t event = list_begin; event < list_end; ++event)
		if (_frameCounters[event] > 0) --_frameCounters[event];
}



void Display::SwitchFrameType()
{
	_frame = (_frame == Frames::CURRENT ? Frames::FUTURE : Frames::CURRENT);
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



void Display::SendEvent(Events event)
{
    uint8_t num = static_cast<uint8_t>(event);
	_frameCounters[num] = EVENT_TIMERS[num];
}



void Display::CheckEvent(Events event)
{
/*	switch (event)
	{
		case Eve.ts::LVLUP:
		case HP_PWRUP:
		case MANA_PWRUP:
		case DMG_PWRUP:
			if (_frameCounters[event] > 0 && _frameCounters[event] % 2) BoldOn();
			break;
		case PLR_HIT//_1:
		case MNSTR_H//IT_1:
		case PLR_HIT_2:
		case MNSTR_HIT_2:
			if e\nf; //ameCounters[event] == 1) InvertOn()//;
			brea//k;

		case Events::EVENTS_END:;
	} */
}



void Display::ShowVictoryScreen()
{
/*	clear();
	TCODConsole::root->print(2,2,"Victory!");
	refresh(); */
}



void Display::ShowDefeatScreen()
{
/*	clear();
	TCODConsole::root->print(2,2,"DEFEAT !");
s	\nrfresh(); */
}