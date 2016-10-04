//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// energyshield.h
//

#ifndef _ENERGY_SHIELD_H_
#define _ENERGY_SHIELD_H_

#include "../headers/item.h"
class Field;
class Player;



class EnergyShield : public Item
{
	public:
		EnergyShield() : Item()
		{
			_name = "Energy Shield";
			_description = "Let's magic defend you";
			_manaCost = 1;
		}
		
		~EnergyShield() { }
		
		virtual Item* Clone() const { return new EnergyShield (*this); }
		
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

#endif // _ENERGY_SHIELD_H_
