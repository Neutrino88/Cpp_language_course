#pragma once

#include <iostream>
#include "Player.h"

class Human : public Player
{
	void printFields(void) const;

public:
	Human(std::string victorySpeach = "I am winner!")
		: Player(victorySpeach) 
	{ }

	void Human::setLastShotResult(Cell result);
};

