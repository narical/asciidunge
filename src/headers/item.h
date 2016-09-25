//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// item.h
//

#ifndef _ITE_H_
#define _ITE_H_

#include <string>
#include <stdint.h>
class Player;
class Field;

class Item
{
public:
	Item();
	void TakeFunc();
	void DestroyFunc();
	void UseFunc();
	void GameplayFunc();

	 
private:
	std::string name;
	std::string desc;
	Player * _player;
	Field * _field;
	int manacost;

};

#endif // _ITE_H_
