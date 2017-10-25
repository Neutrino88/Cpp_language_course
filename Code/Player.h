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
    std::string name;

    void fillCellAroundKilledShip(void) {
        // get lives of ship
        int x = lastShot.x;
        int y = lastShot.y;

        int lx = x;
        int ly = y;

        enemyField.getFirstShipCell(x, y);
        enemyField.getLastShipCell(lx, ly);

        // one-cells ship
        if (x == lx && y == ly) {
            if (y > 0)                    enemyField.f[x][y - 1] = CELL_WATER;
            if (y + 1 < FL_FIELD_SIZE)    enemyField.f[x][y + 1] = CELL_WATER;
            if (x > 0)                    enemyField.f[x - 1][y] = CELL_WATER;
            if (x + 1 < FL_FIELD_SIZE)    enemyField.f[x + 1][y] = CELL_WATER;
        }
        else {
            int dx = 0, dy = 0;

            if (y < ly) {
                dy = 1;
                if (y > 0)                    enemyField.f[x][y - 1] = CELL_WATER;
                if (ly + 1 < FL_FIELD_SIZE)   enemyField.f[x][ly + 1] = CELL_WATER;
            }

            if (x < lx) {
                dx = 1;
                if (x > 0)                    enemyField.f[x - 1][y] = CELL_WATER;
                if (lx + 1 < FL_FIELD_SIZE)   enemyField.f[lx + 1][y] = CELL_WATER;
            }

            for (int i = 0; i <= max(lx - x, ly - y); ++i)
                enemyField.f[x + dx * i][y + dy * i] = CELL_WHOLE_SHIP;
        }
    }
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
    int shipsCount(void) {
        return field.getShipsCount();
    }

    Player(std::string name = "Player")
        : field(CELL_WATER)
        , enemyField(CELL_NOT_KNOWN)
        , name(name)
    {
        AddShips();
    }

    virtual ShotResult getShot(const Cell & shot) {
        // if coordinates isn't correct
        if (shot.x < 0 || FL_FIELD_SIZE <= shot.x || shot.y < 0 || FL_FIELD_SIZE <= shot.y) {
            return SHOTR_MISSED;
        }
        // if hit the ship
        else if (field.f[shot.x][shot.y] == CELL_WHOLE_SHIP) {
            field.f[shot.x][shot.y] = CELL_WOUNDED_SHIP;
            field.decLives(shot.x, shot.y);

            if (field.getLivesOfShipOn(shot.x, shot.y) == 0) {
                return SHOTR_KILLED;
            }

            return SHOTR_WOUNDED;
        }
        // if don't hit the ship
        else {
            return SHOTR_MISSED;
        }
    };

    virtual Cell doShot(void) {
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

    virtual void setLastShotResult(const ShotResult result) { 
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

    virtual std::string getName(void) {
        return name;
    }
};
