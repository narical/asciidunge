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



class Item
{
	public:
		Item();
		virtual ~Item();
		void virtual Use() = 0;
		void SetPosition(Field *);
		std::string GetName() const;
		std::string GetDescription() const;

	protected:
		bool _selected;
		std::string _name;
		std::string _description;
		Field * _field;
		uint8_t manaCost;
};


class SwordOfReadiness : public Item
{
	public:
		SwordOfReadiness();
		~SwordOfReadiness();
		void Use();
};
#endif // _ITEM_H_
