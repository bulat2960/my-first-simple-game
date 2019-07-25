#ifndef CELL_H
#define CELL_H


class Cell
{
private:
    bool state;
public:
    int x;
    int y;
public:
    bool isWall();
    bool isRoad();

    void setWall();
    void setRoad();

    Cell();
    Cell(int x, int y);
};

#endif // CELL_H
