/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * monster.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "headers/monster.h"
#include "headers/player.h"
#include "headers/field.h"



Monster::Monster(uint8_t monsterLevel) : _level( monsterLevel ), _isDead(0)
{

}


/*
Monster::Monster(const Monster &p)
{
	_level = p._level;
	_exp = p._exp;
	_damage = p._damage;
	_HP = p._HP;
	_maxHP = p._maxHP;
	_field = NULL;
	_name = "111"; //p._name;
	_isDead = p._isDead;
}
*/



uint16_t Monster::CalculateDamage(uint8_t monsterLevel)
{
	return (uint16_t)((monsterLevel * (monsterLevel + 5)) / 2);
}


uint16_t Monster::CalculateMaxHP(uint8_t monsterLevel)
{
	return (monsterLevel * (monsterLevel + 6) - 1);
}


void Monster::Attack(Player * plr)
{
	plr->TakeDamage(_damage);
}


void Monster::AddHP(uint16_t delta)
{
	_HP = (_HP + delta > _maxHP ? _maxHP : _HP + delta);
}


void Monster::TakeDamage(Player * plr)
{
	uint16_t delta = plr->GetDamage();
	_HP = (_HP - delta < 0 ? 0 : _HP - delta);
	if (_HP == 0) _isDead = 1;
}


bool Monster::IsDead()
{
	return _isDead;
}


bool Monster::IsAlive()
{
	return !_isDead;
}


std::string Monster::GetName() const
{
	return _name;
}


uint8_t Monster::GetLevel() const
{
	return _level;
}


uint16_t Monster::GetDamage() const
{
	return _damage;
}


uint16_t Monster::GetHP() const
{
	return _HP;
}


uint16_t Monster::GetMaxHP() const
{
	return _maxHP;
}



//==============================================================//
//																//
//					BEGIN OF MONSTER SUBCLASSES					//
//																//
//==============================================================//



Goblin::Goblin(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "goblin";
}



Skeleton::Skeleton(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "skeleton";
}



Zombie::Zombie(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "zombie";
}



Troll::Troll(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "troll";
}



Rogue::Rogue(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "rogue";
}



Mage::Mage(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "mage";
}



Golem::Golem(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "golem";
}



Ghost::Ghost(uint8_t monsterLevel) : Monster(monsterLevel)
{
	_damage = CalculateDamage( monsterLevel );
	_maxHP = CalculateMaxHP( monsterLevel );
	_HP = _maxHP;
	_name = "ghost";
}

