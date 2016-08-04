/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * monster.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "monster.h"
int Monster::s_Quantity = 0;

Monster::Monster(int monsterLevel) : m_level( monsterLevel ), m_isDead(0)
{
	++s_Quantity;
	m_damage = CalculateDamage( monsterLevel );
	m_maxHP = CalculateMaxHP( monsterLevel );
	m_HP = m_maxHP;
	switch (rand() % 8)
	{
		case 0: m_name = "goblin"; break;
		case 1: m_name = "skeleton"; break;
		case 2: m_name = "zombie"; break;
		case 3: m_name = "troll"; break;
		case 4: m_name = "rogue"; break;
		case 5: m_name = "mage"; break;
		case 6: m_name = "golem"; break;
		case 7: m_name = "ghost";
	}
}


int Monster::CalculateDamage(int monsterLevel)
{
	return (int)((monsterLevel * (monsterLevel + 5)) / 2);
}


int Monster::CalculateMaxHP(int monsterLevel)
{
	return (monsterLevel * (monsterLevel + 6) - 1);
}


void Monster::Attack(Player * plr)
{
	plr->LoseHP(m_damage);
}


void Monster::AddHP(int delta)
{
	m_HP = (m_HP + delta > m_maxHP ? m_maxHP : m_HP + delta);
}


void Monster::TakeDamage(Player * plr)
{
	int delta = plr->GetDamage();
	m_HP = (m_HP - delta < 0 ? 0 : m_HP - delta);
	if (m_HP == 0) {m_isDead = 1; --s_Quantity;}
}


bool Monster::IsDead()
{
	return m_isDead;
}


bool Monster::IsAlive()
{
	return !m_isDead;
}


std::string Monster::GetName() const
{
	return m_name;
}


int Monster::GetLevel() const
{
	return m_level;
}


int Monster::GetDamage() const
{
	return m_damage;
}


int Monster::GetHP() const
{
	return m_HP;
}


int Monster::GetMaxHP() const
{
	return m_maxHP;
}

