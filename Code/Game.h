#pragma once

#include "Player.h"
#include "Bot.h"
#include "Human.h"
#include <iostream>

class Game{
    Player* player1;
    Player* player2;

public:
    Game(Player * player1, Player * player2);

    int start(void);
};
