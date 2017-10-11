#pragma once

#include "Field.h"
#include <cstdlib>
#include <string>
#include <ctime>

struct Shot {
	int x = -1;
	int y = -1;
	Cell result = CELL_NOT_KNOWN;
};

class Player{

protected:
	Shot lastShot;
	std::string vicSpeach;

	virtual void AddShips(void) {
		field.addShip(1, 1, 1, 1);
		field.addShip(3, 8, 3, 8);
		field.addShip(7, 1, 7, 1);
		field.addShip(8, 5, 8, 5);

		field.addShip(1, 4, 1, 5);
		field.addShip(6, 4, 6, 5);
		field.addShip(8, 8, 9, 8);

		field.addShip(0, 7, 0, 9);
		field.addShip(3, 0, 5, 0);

		field.addShip(9, 0, 9, 3);
	}

public:
	Player(std::string victorySpeach = "I am winner!")
		: field(CELL_WATER), enemyField(CELL_NOT_KNOWN), vicSpeach(victorySpeach)
	{ 
		AddShips();
	}

	Field field;
	Field enemyField;

	virtual int getShot(Shot & shot) {
		if (shot.x < 0 || FL_FIELD_SIZE <= shot.x || shot.y < 0 || FL_FIELD_SIZE <= shot.y) {
			shot.result = CELL_NOT_KNOWN;
		}
		else if (field.f[shot.x][shot.y] == CELL_WHOLE_SHIP) {
			shot.result = field.f[shot.x][shot.y] = CELL_WOUNDED_SHIP;
			field.decLives(shot.x, shot.y);
		}
		else {
			shot.result = CELL_WATER;
		}

		return field.getShipsCount();
	};

	virtual Shot doShot(void) {
		srand((unsigned int)time(0) + rand());

		for (int i = 0; i < FL_FIELD_SIZE * FL_FIELD_SIZE; ++i) {
			lastShot.x = rand() % FL_FIELD_SIZE;
			lastShot.y = rand() % FL_FIELD_SIZE;

			if (enemyField.f[lastShot.x][lastShot.y] == CELL_NOT_KNOWN)
				break;
		}

		enemyField.f[lastShot.x][lastShot.y] = CELL_WATER;
		return lastShot;
	}

	virtual void setLastShotResult(Cell result) { 
		enemyField.f[lastShot.x][lastShot.y] = result;
	}

	virtual std::string victorySpeach(void) {
		return vicSpeach;
	}
};
