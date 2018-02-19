//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// mightystrike.h
//

#ifndef _MIGHTYSTRIKE_H_
#define _MIGHTYSTRIKE_H_

#include <item.h>
class Field;
class Player;



class MightyStrike : public Item
{
	public:
		MightyStrike() : Item()
		{
			_name = "Mighty Strike";
			_description = "This powerful blow grants 30% bonus damage";
			_manaCost = 6;
		}

		~MightyStrike() { }

		virtual Item* Clone() const { return new MightyStrike (*this); }

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

#endif // _MIGHTYSTRIKE_H_
