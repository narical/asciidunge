//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// Fireball.h
//

#ifndef _FIREBALL_H_
#define _FIREBALL_H_

#include <item.h>
class Field;
class Player;



class Fireball : public Item
{
	public:
		Fireball() : Item()
		{
			_name = "Fireball";
			_description = "Fire death from above!";
			_manaCost = 6;
		}

		~Fireball() { }

		virtual Item* Clone() const { return new Fireball (*this); }

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

#endif // _FIREBALL_H_
