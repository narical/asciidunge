/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * input.h
 * Copyright (C) 2016 Unknown <jnarical@gmail.com>
 *
 */

#ifndef _INPUT_H_
#define _INPUT_H_

class Battlefield;



class Input
{
	public:
		Input(Battlefield *);
		void GetPlayerInput();
		static void WaitAnyKey();

	private:
		Battlefield * _battlefield;

};

#endif // _INPUT_H_
