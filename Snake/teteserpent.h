#ifndef TETESERPENT_H
#define TETESERPENT_H

#include "partieserpent.h"

class TeteSerpent : public PartieSerpent
{
            Q_OBJECT
public:
    TeteSerpent(QRectF* tailleBoule, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);//style graphics de item
    void setAngle(int newAngle);

protected:
    int angle;
};

#endif // TETESERPENT_H
