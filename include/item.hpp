//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// item.h
//

#ifndef _ITEM_H_
#define _ITEM_H_

#include "config.hpp"
#include "field.hpp"
#include "player.hpp"
#include <string>



class Item
{
	public:
		Item() : _state(NOT_SET), _field(nullptr), _manaCost(0) { }
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



#endif // _ITEM_H_
