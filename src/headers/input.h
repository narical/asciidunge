//
// Copyright (c) 2016 Joy Narical <jnarical@gmail.com> MIT license
//
// input.h
//

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
