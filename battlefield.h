/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * battlefield.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_

#include "ncurses.h"
#include <string>
#include "field.h"

class Battlefield {
	
	public:
		Battlefield();
		void Show();
		Field * GetField(int, int);
		 
	private:
		Field *field[20][20];
};

#endif // _BATTLEFIELD_H_

