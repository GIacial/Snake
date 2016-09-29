#include "pomme.h"

Pomme::Pomme(QRectF *tailleBoule, QGraphicsItem *parent):Boule(tailleBoule,parent)
{
    this->setColor(QColor(255,80,80));
}

void Pomme::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){
    bool down = option->state & QStyle::State_Sunken;
            QRectF r = boundingRect();
            QLinearGradient grad(r.topLeft(), r.bottomRight());

            //pomme
            grad.setColorAt(down ? 0 : 1, color);
            painter->setPen(color.darker());
            painter->setBrush(grad);
            painter->drawEllipse(r);
            //tige
            grad.setColorAt(down ? 0 : 1, Qt::green);
            painter->setPen(QColor(Qt::green).darker());
            painter->setBrush(grad);
            QPolygon tige = QPolygon();
            tige << QPoint(r.width()/2,0);
            tige << QPoint(5+r.width()/2,0);
            tige << QPoint(5+r.width()/2,r.height()/4);
            tige << QPoint(r.width()/2,r.height()/4);
            painter->drawPolygon(tige);




}
