//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// item.h
//

#ifndef _ITEM_H_
#define _ITEM_H_

#include <config.h>
#include <field.h>
#include <player.h>
#include <string>



class Item
{
	public:
		Item() : _state(NOT_SET), _field(nullptr) { }
		virtual ~Item() { }
		virtual Item * Clone() const = 0;
		virtual void Use(Player *) { }

		void SetPosition(Field * position) { _field = position; }
		std::string GetName() const { return _name; }
		std::string GetDescription() const { return _description; }
		uint8_t GetManaCost() const { return _manaCost; }
		itemstate GetState() const { return _state; }
		void SetState(itemstate state) { _state = state; }

	protected:
		itemstate _state;
		std::string _name;
		std::string _description;
		Field * _field;
		uint8_t _manaCost;
};

#endif // _ITEM_H_
