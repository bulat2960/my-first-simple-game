#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    int x;
    int y;

    bool state;
public:
    bool isWall();
    bool isRoad();

    void setWall();
    void setRoad();

    Cell();
    Cell(int x, int y);
};

#endif // CELL_H
