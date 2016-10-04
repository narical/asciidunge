//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// swordofreadiness.h
//

#ifndef _SWORD_H_
#define _SWORD_H_

#include "../headers/item.h"
class Field;
class Player;



class SwordOfReadiness : public Item
{
	public:
		SwordOfReadiness() : Item()
		{
			_name = "Sword of Readiness";
			_description = "Grants FIRST STRIKE ability";
			_manaCost = 3;
		}
		
		~SwordOfReadiness() { }
		
		virtual Item* Clone() const { return new SwordOfReadiness (*this); }
		
		virtual void Use(Player * player)
		{
			switch (_state)
			{
				case PREPARED:
					player->SetInitiative(_bonus_initiative);
					_state = ACTIVE;
					break;

				case ACTIVE:
					player->SetInitiative(-_bonus_initiative);
					_state = NOT_SET;
					break;

				case NOT_SET:;
			}
		}
		
	private:
		uint16_t _bonus_initiative = 100;
};

#endif // _SWORD_H_
