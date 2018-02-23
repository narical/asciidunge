//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// heal.h
//

#ifndef _HEAL_H_
#define _HEAL_H_

#include "item.hpp"
class Field;
class Player;



class Heal : public Item
{
	public:
		Heal() : Item()
		{
			_name = "Tome of healing";
			_description = "Healing power of magic";
			_manaCost = 7;
		}

		~Heal() { }

		virtual Item* Clone() const { return new Heal (*this); }

		virtual void Use(Player * player)
		{
			switch (_state)
			{
				case PREPARED:
					// ADD CHANGE HERE
					_state = ACTIVE;
					break;

				case ACTIVE:
					// REMOVE ANY CHANGES HERE
					_state = NOT_SET;
					break;

				case NOT_SET:;
			}
		}

	private:
		// PRIVATE VARS IF ANY
};

#endif // _HEAL_H_
