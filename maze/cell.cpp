#include "cell.h"

Cell::Cell()
{

}

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Cell::setRoad()
{
    this->state = 0;
}

void Cell::setWall()
{
    this->state = 1;
}

bool Cell::isWall()
{
    return this->state == 1;
}

bool Cell::isRoad()
{
    return this->state == 0;
}
