#pragma once

#include <iostream>
#include <memory>

#include "Bot.h"
#include "Human.h"

class Game{
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;

public:
    Game(Player * player1, Player * player2);

    int start(void);
};
