#pragma once

#include "Player.h"

#define min(a,b)	(((a) < (b)) ? (a) : (b))
#define max(a,b)	(((a) > (b)) ? (a) : (b))

class Bot : public Player
{
	Shot penultimateShot;

	/*
	Return square in each cell of which to can set the one-cell ship

	cell should be:
		CELL_NOT_KNOWN for ENEMY_FIELD
		
	*/
	void getMaxEmptySqOnField(const Field & field, const Cell cell, int & resultX, int & resultY, int & resultSize) const;

	//void AddShips(void);

public:
	Bot(std::string victorySpeach);

	//Shot doShot(void);
};