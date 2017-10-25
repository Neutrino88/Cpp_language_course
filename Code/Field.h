#pragma once

#define FL_FIELD_SIZE 10 
#define FL_MAX_SHIP_LEN 4 

enum CellValue {
    CELL_WATER,
    CELL_WHOLE_SHIP,
    CELL_WOUNDED_SHIP,
    CELL_NOT_KNOWN
};

struct Cell {
    int x;
    int y;

    Cell(int x = 0, int y = 0)
        : x(x)
        , y(y)
    { }
};

struct Field{
    CellValue f[FL_FIELD_SIZE][FL_FIELD_SIZE];

    Field() = delete;
    Field(CellValue baseCell);
    
    int getLivesOfShipOn(int x, int y) const;

    /*
    Add ship to field.
    x0 - first cell of ship by X axis.
    y0 - first cell of ship by Y axis.
    x1 - last cell of ship by X axis.
    y1 - last cell of ship by Y axis.
    */
    bool addShip(int x0, int y0, int x1, int y1);

    /*
    Return ships count
    */
    int getShipsCount(void) const;

    /* 
    Dec lives of ship on (x, y).
    */
    void decLives(const int x, const int y);

    void getFirstShipCell(int & x, int & y) const;
    void getLastShipCell(int & x, int & y) const;

private:
    int lives;
    int shipsCount;
    bool gameProcess;
};
