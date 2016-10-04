//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// config.h
//

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <cstdint>

enum frametype  {CURRENT, FUTURE};
enum poweruptype{HEALTH, MANA, DAMAGE};
enum direction  {LEFT, RIGHT, UP, DOWN, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
enum itemstate {NOT_SET, PREPARED, ACTIVE};
enum eventtype  {LVLUP, HP_PWRUP, MANA_PWRUP, DMG_PWRUP,
				PLR_HIT_1, MNSTR_HIT_1, PLR_HIT_2, MNSTR_HIT_2,
				EVENTS_END};

const uint8_t EVENT_TIMERS[] = {6, 6, 6, 6, 1, 1, 2, 2, 0};
const uint8_t CURVE_COEFF[] = {5, 6, 7, 8, 9, 10, 11, 12};
const uint8_t SUM_COEFF = 68;

// Battlefield
const uint8_t BF_SIZE = 20;
const uint8_t ITEMS_QUANTITY = 5;
const uint8_t POWERUPS_QUANTITY_BY_TYPE[3] = {5,5,5}; //health, mana, damage
const uint8_t MONSTERS_QUANTITY_BY_LEVEL[11] = {0,10,5,4,4,4,3,3,3,2,1}; //Quantity of monsters of each level

// Player
const uint8_t START_EXP = 0;
const uint8_t START_LEVEL = 1;
const uint8_t START_MAX_MANA = 10;

const uint8_t MANA_PER_FIELD = 1;
const uint8_t DAMAGE_PER_LEVEL = 5;
const uint8_t HEALTH_PER_LEVEL = 10;
const uint8_t NEXT_LEVEL_MULTIPLIER = 5;

// Powerup
const uint8_t POWERUP_MANA_BONUS = 1;
const uint8_t POWERUP_DAMAGE_BONUS = 10; //in percents

// Display
const uint8_t BARWIDTH = 20;
const uint8_t BF_ROW = 1;
const uint8_t PLAYER_ROW = 1;
const uint8_t ENEMY_ROW = 18;
const uint8_t BF_MARGIN = 2;
const uint8_t INFO_MARGIN = 26;
const uint8_t BAR_MARGIN = 45;

#endif // _CONFIG_H_

