#include "Bot.h"

Bot::Bot(std::string name = "Bot")
    : Player(name)
{ }

void Bot::getMaxEmptySqOnField(const Field & field, const CellValue cell, int & resultX, int & resultY, int & resultSize) const{
    int arr[FL_FIELD_SIZE + 1][FL_FIELD_SIZE + 1];

    // Init array
    for (int h = 0; h < FL_FIELD_SIZE; ++h)
        for (int w = 0; w < FL_FIELD_SIZE; ++w) {
            if (field.f[h][w] == cell)
                arr[h][w] = 0;
            else {
                arr[h][w] = -1;
            }
        }

    // Fill array
    for (int h = 0; h < FL_FIELD_SIZE; ++h) {
        for (int w = 0; w < FL_FIELD_SIZE; ++w) {
            if (arr[h][w] < 0) continue;

            int a = (h > 0) ? arr[h - 1][w] : 0;
            int b = (w > 0) ? arr[h][w - 1] : 0;
            int c = (h > 0 && w > 0) ? arr[h - 1][w - 1] : 0;

            arr[h][w] = max(min(min(a, b), c) + 1, 1);
        }
    }

    // search Max item
    resultSize = -1;
    int countMax = 0;

    for (int h = 0; h < FL_FIELD_SIZE; ++h)
        for (int w = 0; w < FL_FIELD_SIZE; ++w)
            if (arr[h][w] >= resultSize) {
                resultSize = arr[h][w];
                ++countMax;
            }

    countMax = rand() % countMax;

    for (int h = 0; h < FL_FIELD_SIZE; ++h) {
        if (countMax > 0)
        for (int w = 0; w < FL_FIELD_SIZE; ++w)
            if (arr[h][w] >= resultSize && countMax > 0) {
                resultSize = arr[h][w];
                resultX = w;
                resultY = h;
                --countMax;
            }
    }

    if (resultSize > -1) {
        resultX -= (resultSize - 1);
        resultY -= (resultSize - 1);
    }

    std::cout << std::endl;
    for (int h = 0; h < FL_FIELD_SIZE; ++h) {
        for (int w = 0; w < FL_FIELD_SIZE; ++w) {
            std::cout << arr[h][w] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Cell Bot::doShot(void) {
    if (enemyField.f[lastShot.x][lastShot.y] != CELL_WOUNDED_SHIP &&
        enemyField.f[penultShot.x][penultShot.y] == CELL_WOUNDED_SHIP)
    {
        lastShot = penultShot;
    }

    penultShot = lastShot;

    if (enemyField.f[lastShot.x][lastShot.y] == CELL_WOUNDED_SHIP) {
        if (lastShot.x > 0 && enemyField.f[lastShot.x - 1][lastShot.y] == CELL_NOT_KNOWN) {
            --lastShot.x;
        }
        else if (lastShot.y > 0 && enemyField.f[lastShot.x][lastShot.y - 1] == CELL_NOT_KNOWN) {
            --lastShot.y;
        }
        else if (lastShot.x + 1 < FL_FIELD_SIZE && enemyField.f[lastShot.x + 1][lastShot.y] == CELL_NOT_KNOWN) {
            ++lastShot.x;
        }
        else if (lastShot.y + 1 < FL_FIELD_SIZE && enemyField.f[lastShot.x][lastShot.y + 1] == CELL_NOT_KNOWN) {
            ++lastShot.y;
        }
    }
    else {
        srand((unsigned int)time(0) + rand());

        while (true) {
            lastShot.x = rand() % FL_FIELD_SIZE;
            lastShot.y = rand() % FL_FIELD_SIZE;

            if (enemyField.f[lastShot.x][lastShot.y] == CELL_NOT_KNOWN)
                break;
        }

        enemyField.f[lastShot.x][lastShot.y] = CELL_WATER;
    }

    return lastShot;
};
