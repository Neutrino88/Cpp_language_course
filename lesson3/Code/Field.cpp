#include "Field.h"

Field::Field(CellValue baseCell = CELL_WATER)
    : lives(0)
    , shipsCount(0)
    , gameProcess(false)
{
    for (int x = 0; x < FL_FIELD_SIZE; ++x)
        for (int y = 0; y < FL_FIELD_SIZE; ++y) {
            f[x][y] = baseCell;
        }
}

int Field::getLivesOfShipOn(const Cell & cell) const {
	Cell fcell(cell.x, cell.y);
	Cell lcell(cell.x, cell.y);

    getFirstShipCell(fcell);
    getLastShipCell(lcell);

    // get ship lives
    int result = 0;

    while (fcell.x <= lcell.x && fcell.y <= lcell.y) {
        if (f[fcell.x][fcell.y] == CELL_WHOLE_SHIP)
            ++result;

        if (fcell.x == lcell.x) ++fcell.y;
        else                    ++fcell.x;
    }

    return result;
}

bool Field::addShip(Cell fcell, Cell lcell){
    // check for corectness
    if (gameProcess)
        return false;

    // swap coord for order
    if (fcell.x > lcell.x) {
		fcell.x ^= lcell.x; lcell.x ^= fcell.x; fcell.x ^= lcell.x;
    }
    if (fcell.y > lcell.y) {
		fcell.y ^= lcell.y; lcell.y ^= fcell.y; fcell.y ^= lcell.y;
    }

    if ((fcell.x != lcell.x && fcell.y != lcell.y) || fcell.x < 0 || fcell.y < 0 ||
		lcell.x >= FL_FIELD_SIZE || lcell.y >= FL_FIELD_SIZE ||
		lcell.x - fcell.x >= FL_MAX_SHIP_LEN || lcell.y - fcell.y >= FL_MAX_SHIP_LEN) {

        return false;
    }

    // if ship already has been on this place
    for (int x = fcell.x - 1; x < lcell.x + 2; ++x)
        for (int y = fcell.y - 1; y < lcell.y + 2; ++y) {
            if (x < 0 || y < 0) continue;

            if (f[x][y] == CELL_WHOLE_SHIP) {
                return false;
            }
        }

    // add ship to place
    for (int i = 0; i < (lcell.x - fcell.x + lcell.y - fcell.y) + 1; ++i) {
        if (fcell.x != lcell.x) {
            f[fcell.x + i][fcell.y] = CELL_WHOLE_SHIP;
        }
        else {
            f[fcell.x][fcell.y + i] = CELL_WHOLE_SHIP;
        }
    }

    lives += (lcell.x - fcell.x + lcell.y - fcell.y) + 1;
    ++shipsCount;
    return true;
}

int Field::getShipsCount(void) const {
    return shipsCount;
}

void Field::decLives(const Cell & cell) {
    --lives;

    if (getLivesOfShipOn(cell) == 0) {
        --shipsCount;
    }
};

void Field::getFirstShipCell(Cell & cell) const {
    // move to the ship first cell
    while (f[cell.x][cell.y] == CELL_WHOLE_SHIP || f[cell.x][cell.y] == CELL_WOUNDED_SHIP) {
        if (cell.x > 0 && (f[cell.x - 1][cell.y] == CELL_WHOLE_SHIP || f[cell.x - 1][cell.y] == CELL_WOUNDED_SHIP))
            --cell.x;
        else if (cell.y > 0 && (f[cell.x][cell.y - 1] == CELL_WHOLE_SHIP || f[cell.x][cell.y - 1] == CELL_WOUNDED_SHIP))
            --cell.y;
        else break;
    }
}

void Field::getLastShipCell(Cell & cell) const {
    // move to the ship last cell
    while (f[cell.x][cell.y] == CELL_WHOLE_SHIP || f[cell.x][cell.y] == CELL_WOUNDED_SHIP) {
        if (cell.x+1 < FL_FIELD_SIZE && (f[cell.x + 1][cell.y] == CELL_WHOLE_SHIP || f[cell.x + 1][cell.y] == CELL_WOUNDED_SHIP))
            ++cell.x;
        else if (cell.y+1 < FL_FIELD_SIZE && (f[cell.x][cell.y + 1] == CELL_WHOLE_SHIP || f[cell.x][cell.y + 1] == CELL_WOUNDED_SHIP))
            ++cell.y;
        else break;
    }
}
