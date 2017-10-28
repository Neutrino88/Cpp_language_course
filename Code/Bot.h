#pragma once

#include "Player.h"
#include <iostream>

class Bot 
    : public Player
{
	Cell firstCellLastShip;
	bool fireWay[5] = {false, false, false, false, false};

    /*
    for next doShot() version 

    Return square in each cell of which to can set the one-cell ship

    cell should be:
        CELL_NOT_KNOWN for ENEMY_FIELD
        
    */
    void getMaxEmptySqOnField(const Field & field, const CellValue cell, int & resultX, int & resultY, int & resultSize) const;

public:
    Bot(void);

    Cell doShot(void);
};