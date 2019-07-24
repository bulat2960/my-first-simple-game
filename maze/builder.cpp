#include "builder.h"

Builder::Builder(int height, int width)
{
    this->height = height;
    this->width = width;

    this->matrix = QVector<QVector<Cell>>(height, QVector<Cell>(width));
    this->visitMatrix = QVector<QVector<State>>(height, QVector<State>(width));
}

void Builder::initMatrix()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            matrix[y][x] = Cell(x, y);

            bool even = (x % 2 == 0) && (y % 2 == 0);
            bool inside = (y < height) && (x < width);

            if (even && inside)
            {
                matrix[y][x].setRoad();
            }
            else
            {
                matrix[y][x].setWall();
            }
        }
    }
}

void Builder::initVisitMatrix()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            visitMatrix[i][j] = Builder::NOT_VISITED;
        }
    }
}

QVector<Cell> Builder::getNeighbours(const Cell &c)
{
    Cell up    = Cell(c.x, c.y - 2);
    Cell down  = Cell(c.x, c.y + 2);
    Cell left  = Cell(c.x - 2, c.y);
    Cell right = Cell(c.x + 2, c.y);

    QVector<Cell> cells = {up, down, left, right};
    QVector<Cell> neighbours;

    for (const auto& cell : cells)
    {
        bool isInsideByX = (cell.x >= 0 && cell.x < width);
        bool isInsideByY = (cell.y >= 0 && cell.y < height);
        if (isInsideByX && isInsideByY)
        {
            Cell& neighbour = matrix[cell.y][cell.x];
            if (visitMatrix[cell.y][cell.x] == NOT_VISITED)
            {
                neighbours.push_back(neighbour);
            }
        }
    }

    return neighbours;
}

void Builder::removeWall(const Cell &current, const Cell &neighbour)
{
    int x = (current.x + neighbour.x) / 2;
    int y = (current.y + neighbour.y) / 2;
    matrix[y][x].setRoad();
}

void Builder::destroyHorizontal()
{
    int destroyCount = static_cast<int>(round(width / 5));
    while (destroyCount > 0)
    {
        int x = 2 * (rand() % (width / 2));
        if (matrix[height - 1][x].isWall())
        {
            matrix[height - 1][x].setRoad();
            destroyCount--;
        }
    }
}

void Builder::destroyVertical()
{
    int destroyCount = static_cast<int>(round(height / 5));
    while (destroyCount > 0)
    {
        int x = 2 * (rand() % (height / 2));
        if (matrix[x][width - 1].isWall())
        {
            matrix[x][width - 1].setRoad();
            destroyCount--;
        }
    }
}

QVector<QVector<Cell>> Builder::create()
{
    initMatrix();
    initVisitMatrix();

    Cell& current = matrix[0][0];
    visitMatrix[0][0] = Builder::VISITED;

    while (true)
    {
        QVector<Cell> neighbours = getNeighbours(current);

        if (neighbours.size() != 0)
        {
            stack.push(current);

            int randNeighbourNumber = rand() % neighbours.size();
            Cell& neighbour = neighbours[randNeighbourNumber];

            removeWall(current, neighbour);
            visitMatrix[neighbour.y][neighbour.x] = Builder::VISITED;
            current = neighbour;
        }
        else
        {
            if (stack.size() > 0)
            {
                current = stack.top();
                stack.pop();
            }
            else
            {
                break;
            }
        }
    }

    destroyVertical();
    destroyHorizontal();

    return matrix;
}
