/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * monster.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "monster.h"
bool Monster::bossIsDead = FALSE;

Monster::Monster(uint8_t monsterLevel) : m_level( monsterLevel ), m_isDead(0)
{
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


/*
Monster::Monster(const Monster &p)
{
	m_level = p.m_level;
	m_exp = p.m_exp;
	m_damage = p.m_damage;
	m_HP = p.m_HP;
	m_maxHP = p.m_maxHP;	
	m_field = NULL;
	m_name = "111"; //p.m_name;
	m_isDead = p.m_isDead;
}
*/



uint8_t Monster::CalculateDamage(uint8_t monsterLevel)
{
	return (uint8_t)((monsterLevel * (monsterLevel + 5)) / 2);
}


uint8_t Monster::CalculateMaxHP(uint8_t monsterLevel)
{
	return (monsterLevel * (monsterLevel + 6) - 1);
}


void Monster::Attack(Player * plr)
{
	plr->TakeDamage(m_damage);
}


void Monster::AddHP(uint8_t delta)
{
	m_HP = (m_HP + delta > m_maxHP ? m_maxHP : m_HP + delta);
}


void Monster::TakeDamage(Player * plr)
{
	uint8_t delta = plr->GetDamage();
	m_HP = (m_HP - delta < 0 ? 0 : m_HP - delta);
	if (m_HP == 0)
		{
			m_isDead = 1;
			// if it was boss monster, and not a copy
			if (m_level == 10 && plr->GetTargetField()->GetEnemy() == this) bossIsDead = TRUE;
		}
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


uint8_t Monster::GetLevel() const
{
	return m_level;
}


uint8_t Monster::GetDamage() const
{
	return m_damage;
}


uint8_t Monster::GetHP() const
{
	return m_HP;
}


uint8_t Monster::GetMaxHP() const
{
	return m_maxHP;
}

