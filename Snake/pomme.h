#ifndef POMME_H
#define POMME_H

#include "boule.h"

class Pomme : public Boule
{
    Q_OBJECT
public:
    Pomme(QRectF* tailleBoule, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);//style graphics de item
};

#endif // POMME_H
