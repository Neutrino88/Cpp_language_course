#include "Player.h"

Player::Player(void)
	: field(CELL_WATER)
	, enemyField(CELL_NOT_KNOWN)
{
	AddShips();
}

void Player::fillCellAroundKilledShip(void) {
	// get lives of ship
	Cell fcell(lastShot.x, lastShot.y);
	Cell lcell(lastShot.x, lastShot.y);

	enemyField.getFirstShipCell(fcell);
	enemyField.getLastShipCell(lcell);

	// one-cells ship
	if (fcell.x == lcell.x && fcell.y == lcell.y) {
		if (fcell.y > 0)                    enemyField.f[fcell.x][fcell.y - 1] = CELL_WATER;
		if (fcell.y + 1 < FL_FIELD_SIZE)    enemyField.f[fcell.x][fcell.y + 1] = CELL_WATER;
		if (fcell.x > 0)                    enemyField.f[fcell.x - 1][fcell.y] = CELL_WATER;
		if (fcell.x + 1 < FL_FIELD_SIZE)    enemyField.f[fcell.x + 1][fcell.y] = CELL_WATER;
	}
	else {
		int dx = 0, dy = 0;

		if (fcell.y < lcell.y) {
			dy = 1;
			if (fcell.y > 0)                   enemyField.f[fcell.x][fcell.y - 1] = CELL_WATER;
			if (lcell.y + 1 < FL_FIELD_SIZE)   enemyField.f[fcell.x][lcell.y + 1] = CELL_WATER;
		}

		if (fcell.x < lcell.x) {
			dx = 1;
			if (fcell.x > 0)                   enemyField.f[fcell.x - 1][fcell.y] = CELL_WATER;
			if (lcell.x + 1 < FL_FIELD_SIZE)   enemyField.f[lcell.x + 1][fcell.y] = CELL_WATER;
		}

		for (int i = 0; i <= max(lcell.x - fcell.x, lcell.y - fcell.y); ++i)
			enemyField.f[fcell.x + dx * i][fcell.y + dy * i] = CELL_WHOLE_SHIP;
	}
}

void Player::AddShips(void) {
	field.addShip(Cell(1, 1), Cell(1, 1));
	field.addShip(Cell(3, 8), Cell(3, 8));
	field.addShip(Cell(7, 1), Cell(7, 1));
	field.addShip(Cell(8, 5), Cell(8, 5));

	field.addShip(Cell(1, 4), Cell(1, 5));
	field.addShip(Cell(6, 4), Cell(6, 5));
	field.addShip(Cell(8, 8), Cell(9, 8));

	field.addShip(Cell(0, 7), Cell(0, 9));
	field.addShip(Cell(3, 0), Cell(5, 0));

	field.addShip(Cell(9, 0), Cell(9, 3));
}

int Player::shipsCount(void) {
	return field.getShipsCount();
}

ShotResult Player::getShot(const Cell & shot) {
	// if coordinates isn't correct
	if (shot.x < 0 || FL_FIELD_SIZE <= shot.x || shot.y < 0 || FL_FIELD_SIZE <= shot.y) {
		return SHOTR_MISSED;
	}
	// if hit the ship
	else if (field.f[shot.x][shot.y] == CELL_WHOLE_SHIP) {
		field.f[shot.x][shot.y] = CELL_WOUNDED_SHIP;
		field.decLives(shot);

		if (field.getLivesOfShipOn(shot) == 0) {
			return SHOTR_KILLED;
		}

		return SHOTR_WOUNDED;
	}
	// if don't hit the ship
	else {
		return SHOTR_MISSED;
	}
};

Cell Player::doShot(void) {
	srand((unsigned int)time(0) + rand());

	while (true) {
		lastShot.x = rand() % FL_FIELD_SIZE;
		lastShot.y = rand() % FL_FIELD_SIZE;

		if (enemyField.f[lastShot.x][lastShot.y] == CELL_NOT_KNOWN)
			break;
	}

	enemyField.f[lastShot.x][lastShot.y] = CELL_WATER;
	return lastShot;
}

void Player::setLastShotResult(const ShotResult result) {
	if (result == SHOTR_MISSED) {
		enemyField.f[lastShot.x][lastShot.y] = CELL_WATER;
	}
	else {
		// fill diagonal cells CELL_WATER value
		if (lastShot.x > 0 && lastShot.y > 0)                                    enemyField.f[lastShot.x - 1][lastShot.y - 1] = CELL_WATER;
		if (lastShot.x > 0 && lastShot.y + 1 < FL_FIELD_SIZE)                    enemyField.f[lastShot.x - 1][lastShot.y + 1] = CELL_WATER;
		if (lastShot.x + 1 < FL_FIELD_SIZE && lastShot.y > 0)                    enemyField.f[lastShot.x + 1][lastShot.y - 1] = CELL_WATER;
		if (lastShot.x + 1 < FL_FIELD_SIZE && lastShot.y + 1 < FL_FIELD_SIZE)    enemyField.f[lastShot.x + 1][lastShot.y + 1] = CELL_WATER;

		if (result == SHOTR_WOUNDED) {
			enemyField.f[lastShot.x][lastShot.y] = CELL_WOUNDED_SHIP;
		}
		else {
			enemyField.f[lastShot.x][lastShot.y] = CELL_WHOLE_SHIP;
			fillCellAroundKilledShip();
		}
	}
}