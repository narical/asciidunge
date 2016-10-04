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

#endif // _ITEM_H_
