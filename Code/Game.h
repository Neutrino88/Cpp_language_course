#pragma once

#include "Player.h"
#include "Bot.h"
#include "Human.h"
#include <iostream>

class Game{
	Human player1;
	Bot player2;

public:
	Game(const Human & player1, const Bot & player2);

	int start(void);
};

void printField(const Field & field);

