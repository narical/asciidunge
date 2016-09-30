//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// item.h
//

#ifndef _ITEM_H_
#define _ITEM_H_

#include "config.h"
#include <string>
class Field;
class Player;


class Item
{
	public:
		Item();
		virtual ~Item();
		virtual Item * Clone() const = 0;
		virtual void Use(Player *);
		void SetPosition(Field *);
		std::string GetName() const;
		std::string GetDescription() const;
		uint8_t GetManaCost() const;
		itemstate GetState() const;
		void SetState(itemstate);

	protected:
		itemstate _state;
		std::string _name;
		std::string _description;
		Field * _field;
		uint8_t _manaCost;
};


class SwordOfReadiness : public Item
{
	public:
		SwordOfReadiness();
		~SwordOfReadiness();
		Item* Clone() const { return new SwordOfReadiness (*this); }
		void virtual Use(Player *);
		
	private:
		uint16_t _bonus_initiative = 100;
};


class MightyStrike : public Item
{
	public:
		MightyStrike();
		~MightyStrike();
		Item* Clone() const { return new MightyStrike (*this); }
		//void Use();
};


class Fireball : public Item
{
	public:
		Fireball();
		~Fireball();
		Item* Clone() const { return new Fireball (*this); }
		//void Use();
};


class Heal : public Item
{
	public:
		Heal();
		~Heal();
		Item* Clone() const { return new Heal (*this); }
		//void Use();
};


class EnergyShield : public Item
{
	public:
		EnergyShield();
		~EnergyShield();
		Item* Clone() const { return new EnergyShield (*this); }
		//void Use();
};

#endif // _ITEM_H_
