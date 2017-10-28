#pragma once

#include "Field.h"
#include <string>
#include <ctime>

#define min(a,b)    (((a) < (b)) ? (a) : (b))
#define max(a,b)    (((a) > (b)) ? (a) : (b))

enum ShotResult {
    SHOTR_MISSED,
    SHOTR_WOUNDED,
    SHOTR_KILLED,
    SHOTR_LOSED
};

class Player{

protected:
    Field enemyField;
    Field field;
    Cell lastShot;

	virtual void AddShips(void);
	void fillCellAroundKilledShip(void);

public:
	Player(void);

	int shipsCount(void);

	virtual Cell doShot(void);
	virtual ShotResult getShot(const Cell & shot);
	virtual void setLastShotResult(const ShotResult result);
};
