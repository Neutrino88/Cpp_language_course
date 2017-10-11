#pragma once

#define FL_FIELD_SIZE 10 
#define FL_MAX_SHIP_LEN 4 

enum Cell {
	CELL_WATER,
	CELL_WHOLE_SHIP,
	CELL_WOUNDED_SHIP,
	CELL_NOT_KNOWN
};

class Field{
	int lives;
	int shipsCount;
	bool gameProcess;

	int getLivesOfShipOn(int x, int y) const;

public:
	Cell f[FL_FIELD_SIZE][FL_FIELD_SIZE];

	Field() = delete;
	Field(Cell baseCell);
	
	/*
	Add ship to field.
	x0 - first cell of ship by X axis.
	y0 - first cell of ship by Y axis.
	x1 - last cell of ship by X axis.
	y1 - last cell of ship by Y axis.
	*/
	bool addShip(int x0, int y0, int x1, int y1);
	
	/*
	Return cells count with whole ships
	*/
	int getLives(void) const;

	/*
	Return ships count
	*/
	int getShipsCount(void) const;

	/* Dec lives of ship on (x, y).
	*/
	void decLives(const int x, const int y);
};
