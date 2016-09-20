/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * config.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdint.h>

enum frametype   {CURRENT, FUTURE};
enum poweruptype {HEALTH, MANA, DAMAGE};
enum direction   {LEFT, RIGHT, UP, DOWN};
enum eventtype   {NOTHING, LVLUP, HP_PWRUP, MANA_PWRUP, DMG_PWRUP, PLR_HIT, MNSTR_HIT};
const uint8_t EVENT_TIMERS[] = {0, 6, 6, 6, 6, 1, 1};

// Battlefield
const uint8_t BF_SIZE = 20;
const uint8_t POWERUPS_QUANTITY_BY_TYPE[3] = {5,5,5}; //health, mana, damage
const uint8_t MONSTERS_QUANTITY_BY_LEVEL[11] = {0,10,5,4,4,4,3,3,3,2,1}; //Quantity of monsters of each level
const uint8_t HP_PER_FIELD = 2;
const uint8_t MANA_PER_FIELD = 2;

// Player
const uint8_t START_LEVEL =		1;
const uint8_t START_EXP =		0;
const uint8_t START_MAX_EXP =	4;
const uint8_t START_DAMAGE =		5;
const uint8_t START_MAX_HP =		10;
const uint8_t START_MAX_MANA =	10;
const uint8_t SIGHT_RADIUS =		2;
const uint8_t ADD_MAXHP_PER_LVL =   10;
const uint8_t ADD_DAMAGE_PER_LVL =	5;
const uint8_t EXP_TO_NEXT_LVL_MULTIPLIER = 2;

// Powerup
const uint8_t POWERUP_HEALTH_BONUS = 10;
const uint8_t POWERUP_MANA_BONUS = 7;
const uint8_t POWERUP_DAMAGE_BONUS = 5;

// Display
const uint8_t BARWIDTH = 20;
const uint8_t BF_ROW = 1;
const uint8_t PLAYER_ROW = 1;
const uint8_t ENEMY_ROW = 14;
const uint8_t BF_MARGIN = 2;
const uint8_t INFO_MARGIN = 26;
const uint8_t BAR_MARGIN = 45;

#endif // _CONFIG_H_

