#pragma once

#include <iostream>
#include "Player.h"
#include <regex>

class Human 
    : public Player
{
    void printFields(void) const;

public:
    Human(void);

    Cell doShot(void);
};

