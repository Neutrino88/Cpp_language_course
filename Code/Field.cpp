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

int Field::getLivesOfShipOn(int x, int y) const {
    int lx = x;
    int ly = y;

    getFirstShipCell(x, y);
    getLastShipCell(lx, ly);

    // get ship lives
    int result = 0;

    while (x <= lx && y <= ly) {
        if (f[x][y] == CELL_WHOLE_SHIP)
            ++result;

        if (x == lx)    ++y;
        else            ++x;
    }

    return result;
}

bool Field::addShip(int x0, int y0, int x1, int y1){
    // check for corectness
    if (gameProcess)
        return false;

    // swap coord for order
    if (x0 > x1) {
        x0 ^= x1; x1 ^= x0; x0 ^= x1;
    }
    if (y0 > y1) {
        y0 ^= y1; y1 ^= y0; y0 ^= y1;
    }

    if ((x0 != x1 && y0 != y1) || x0 < 0 || y0 < 0 ||
        x1 >= FL_FIELD_SIZE || y1 >= FL_FIELD_SIZE ||
        x1 - x0 >= FL_MAX_SHIP_LEN || y1 - y0 >= FL_MAX_SHIP_LEN) {

        return false;
    }

    // if ship already has been on this place
    for (int x = x0 - 1; x < x1 + 2; ++x)
        for (int y = y0 - 1; y < y1 + 2; ++y) {
            if (x < 0 || y < 0) continue;

            if (f[x][y] == CELL_WHOLE_SHIP) {
                return false;
            }
        }

    // add ship to place
    for (int i = 0; i < (x1 - x0 + y1 - y0) + 1; ++i) {
        if (x0 != x1) {
            f[x0 + i][y0] = CELL_WHOLE_SHIP;
        }
        else {
            f[x0][y0 + i] = CELL_WHOLE_SHIP;
        }
    }

    lives += (x1 - x0 + y1 - y0) + 1;
    ++shipsCount;
    return true;
}

int Field::getShipsCount(void) const {
    return shipsCount;
}

void Field::decLives(const int x, const int y) {
    --lives;

    if (getLivesOfShipOn(x, y) == 0) {
        --shipsCount;
    }
};

void Field::getFirstShipCell(int & x, int & y) const {
    // move to the ship first cell
    while (f[x][y] == CELL_WHOLE_SHIP || f[x][y] == CELL_WOUNDED_SHIP) {
        if (x > 0 && (f[x - 1][y] == CELL_WHOLE_SHIP || f[x - 1][y] == CELL_WOUNDED_SHIP))
            --x;
        else if (y > 0 && (f[x][y - 1] == CELL_WHOLE_SHIP || f[x][y - 1] == CELL_WOUNDED_SHIP))
            --y;
        else break;
    }
}

void Field::getLastShipCell(int & x, int & y) const {
    // move to the ship last cell
    while (f[x][y] == CELL_WHOLE_SHIP || f[x][y] == CELL_WOUNDED_SHIP) {
        if (x+1 < FL_FIELD_SIZE && (f[x + 1][y] == CELL_WHOLE_SHIP || f[x + 1][y] == CELL_WOUNDED_SHIP))
            ++x;
        else if (y+1 < FL_FIELD_SIZE && (f[x][y + 1] == CELL_WHOLE_SHIP || f[x][y + 1] == CELL_WOUNDED_SHIP))
            ++y;
        else break;
    }
}
