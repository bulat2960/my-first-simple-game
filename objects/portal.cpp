#include "portal.h"

Portal::Portal(Sector* sector) : FixedObject(sector)
{
    drawingSettings.image.load(":/images/images/portal.png");

    setStartPosition();
}

QPainterPath Portal::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());

    return path;
}

void Portal::setStartPosition()
{
    int sectorCellCounter = 0;

    for (int x = 0; x < mapPosition.sector->width(); x++)
    {
        for (int y = 0; y < mapPosition.sector->height(); y++)
        {
            bool atVerticalBorders = (x == 0) || (x == mapPosition.sector->width() - 1);
            bool atHorizontalBorders = (y == 0) || (y == mapPosition.sector->height() - 1);
            bool notAtBorders = !(atVerticalBorders || atHorizontalBorders);

            if (mapPosition.sector->cell(x, y).isRoad() && notAtBorders)
            {
                int wallCounter = 0;
                wallCounter += mapPosition.sector->cell(x + 1, y).isWall();
                wallCounter += mapPosition.sector->cell(x - 1, y).isWall();
                wallCounter += mapPosition.sector->cell(x, y + 1).isWall();
                wallCounter += mapPosition.sector->cell(x, y - 1).isWall();

                if (wallCounter < 3 && sectorCellCounter < mapPosition.sector->height() * mapPosition.sector->width())
                {
                    sectorCellCounter++;
                    continue;
                }


                x += mapPosition.sector->position().x() * mapPosition.sector->width();
                y += mapPosition.sector->position().y() * mapPosition.sector->height();
                setPosition(x, y);
                setGraphicalPosition(x, y);
                break;
            }
        }
    }
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawImage(boundingRect(), drawingSettings.image);
}
