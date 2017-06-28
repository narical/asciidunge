//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// player.h
//

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "config.h"
#include <string>

class Monster;
class Field;
class Item;
class Game;



class Player
{
	public:
		Player(Game *);
		Player(const Player &);

		void Act(int);
		void LevelUp();
		void TakeItem();
		void DropItem();
		void LookAround();
		void Move(Field *);
		void ActivateItem();
		void CalculateStats();
		void GainExp(Monster *);
		void HandleItems(std::string);
		eventtype TakePowerup(Field *);

		void Heal() { _HP = _maxHP; }
		void Recover() { _mana = _maxMana; }
		void SetTargetField(Field * fld) { _target = fld; }
		void SetInitiative(uint16_t delta) { _initiative += delta; }
		void TakeDamage(uint16_t delta) { _HP = (_HP - delta < 0 ? 0 : _HP - delta); }
		void SpendMana(uint16_t delta) { _mana = (_mana - delta < 0 ? 0 : _mana - delta); }
		void HealBy(uint16_t delta) { _HP = (_HP + delta > _maxHP ? _maxHP : _HP + delta); }
		void RecoverBy(uint16_t delta) { _mana = (_mana + delta > _maxMana ? _maxMana : _mana + delta); }
		void SelectItem(uint8_t number) { if (_inventory[number] != nullptr) _selectedItem = _inventory[number]; }

		uint16_t GetHP() const { return _HP; }
		uint16_t GetExp() const { return _exp; }
		uint16_t GetMana() const { return _mana; }
		uint8_t GetLevel() const { return _level; }
		uint16_t GetMaxHP() const { return _maxHP; }
		uint16_t GetExpMax() const { return _expMax; }
		uint16_t GetDamage() const { return _damage; }
		uint16_t GetMaxMana() const { return _maxMana; }
		uint16_t GetInitiative() const { return _initiative + _level; }
		std::string GetName() const { return _name; }
		Field* GetPosition() const { return _position; }
		Field* GetTargetField() const { return _target; }
		Item * GetSelectedItem() const { return _selectedItem; }
		Item * GetInventory(uint8_t index) const { return _inventory[index]; }

		bool IsAlive() const { return (_HP > 0 ? true : false); }
		bool IsDead() const { return (_HP <= 0 ? true : false); }
		bool HaveTarget() const { return (_target != nullptr); }

		void TEST_LevelUp();

	private:
		std::string _name;
		Item * _inventory[4];
		uint8_t _level;
		uint16_t _exp;
		uint16_t _expMax;
		uint16_t _damage;
		uint16_t _HP, _maxHP;
		uint16_t _mana, _maxMana;
		uint16_t _initiative;
		uint8_t _powerups[3];

		Item * _selectedItem;
		Field * _position;
		Field * _target;
		
		Game * _game;
};

#endif // _PLAYER_H_

