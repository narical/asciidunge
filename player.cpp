/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * player.cc
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#include "player.h"

Player::Player () : level(1), exp(0), damage(5), HP(0), mana(0), maxHP(100), maxMana(70),
					sightRadius(2), coordRow(10), coordCol(10), name("Nameless")
{

}

void Player::Show()
{

	mvprintw(2, 25, "Name: %s", this->name.c_str());
	mvprintw(3, 25, "Level: %d", this->level);
	mvprintw(4, 25, "HP: %d/%d %s", this->HP, this->maxHP, Game::ShowBar(this->HP, this->maxHP).c_str());
	mvprintw(5, 25, "Mana: %d/%d %s", this->mana, this->maxMana, Game::ShowBar(this->mana, this->maxMana).c_str());
	mvaddch(this->coordRow + 1, this->coordCol + 1, '@');
}

void Player::Move(Battlefield *btl, int input_key)
{
	switch(input_key) {
		case KEY_LEFT:
			if (this->coordCol > 0) this->coordCol -= 1;
			break;
		case KEY_RIGHT:
			if (this->coordCol < 19) this->coordCol += 1;
			break;
		case KEY_UP:
			if (this->coordRow > 0) this->coordRow -= 1;
			break;
		case KEY_DOWN:
			if (this->coordRow < 19) this->coordRow += 1;
	}
	this->LookAround(btl);
}

void Player::LookAround(Battlefield *btl)
{
	int R    = this->sightRadius;
	int X    = this->coordCol;
	int Xmin = this->coordCol;
	int Xmax = this->coordCol;
	int Y    = this->coordRow;
	int Ymin = this->coordRow;
	int Ymax = this->coordRow;

	for (int i = 0; i <= R; ++i) {	// Определяем границы области видимости, чтобы
		if (Xmin - i <= 0) Xmin = 0;				// не уйти за край карты
		else --Xmin;
		if (Xmax + i >= 19) Xmax = 19;
		else ++Xmax;
		if (Ymin - i <= 0) Ymin = 0;
		else --Ymin;
		if (Ymax + i >= 19) Ymax = 19;
		else ++Ymax;
	}

	for (int i = Xmin; i <= Xmax; ++i)
		for (int j = Ymin; j <= Ymax; ++j)
			if ( (X-i)*(X-i)+(Y-j)*(Y-j) <= R*R )
			{
				Field *field = btl->GetField(j,i);
				field->MakeVisible();
				this->AddMana(field->GetMana());
				this->AddHP(field->GetHP());
			}
}


void Player::SetMana(int newQuantity)
{
	this->mana = newQuantity;
	//TODO: добавить проверку
}


void Player::SetManaFull()
{
	this->mana = this->maxMana;
}


void Player::AddMana(int delta)
{
	int mana = this->mana;
	int maxMana = this->maxMana;
	this->mana = (mana + delta > maxMana ? maxMana : mana + delta);
}


void Player::LoseMana(int delta)
{
	int mana = this->mana;
	this->mana = (mana - delta < 0 ? 0 : mana - delta);
}


void Player::SetHP(int newQuantity)
{
	this->HP = newQuantity;
	//TODO: добавить проверку
}


void Player::SetHpFull()
{
	this->HP = this->maxHP;
}


void Player::AddHP(int delta)
{
	int HP = this->HP;
	int maxHP = this->maxHP;
	this->HP = (HP + delta > maxHP ? maxHP : HP + delta);
}


void Player::LoseHP(int delta)
{
	int HP = this->HP;
	this->HP = (HP - delta < 0 ? 0 : HP - delta);
	//if (this->HP == 0) this->kill();
	//TODO: Game Over
}

void Player::SetTarget(Field * rTarget)
{
				this->target = rTarget;
}

Field * Player::GetTarget()
{
	return 	this->target;
}

/*
void Show();
std::string GetName();
void Kill();
*/

