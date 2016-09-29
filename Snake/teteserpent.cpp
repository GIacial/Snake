#include "teteserpent.h"

TeteSerpent::TeteSerpent(QRectF *tailleBoule, QGraphicsItem *parent): PartieSerpent(tailleBoule,parent)
{
    angle=0;

}

void TeteSerpent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){
    bool down = option->state & QStyle::State_Sunken;
            QRectF r = boundingRect();
            QLinearGradient grad(r.topLeft(), r.bottomRight());
            grad.setColorAt(down ? 0 : 1, color);
            painter->setPen(color);
            painter->setBrush(grad);
            painter->drawEllipse(r);

            //bord noir
            painter->setBrush(Qt::NoBrush);
            painter->setPen(color.darker());
            painter->drawEllipse(r);

            //yeux                                   //0=>haut 1=>droite 2=>bas 3=>gauche
            QRectF rectEyes = QRectF(r.width()/4,r.height()/4,r.width()/4,r.height()/4);
            grad.setColorAt(down ? 0 : 1,Qt::white);
            painter->setBrush(grad);
            painter->drawEllipse(rectEyes);
            rectEyes.setX(3*r.width()/4);
            painter->drawEllipse(rectEyes);

            //
            QRectF rectEyesIn = QRectF(3*r.width()/8,r.height()/4,r.width()/8,r.height()/8);
            grad.setColorAt(down ? 0 : 1,Qt::black);
            painter->setBrush(grad);
            painter->drawEllipse(rectEyesIn);
            rectEyesIn.setX(5*r.width()/8);
            painter->drawEllipse(rectEyesIn);

            this->setTransformOriginPoint(taille->width()/2,taille->height()/2);//on centre la rotation
            this->setRotation(angle);

}

void TeteSerpent::setAngle(int newAngle){
    angle=newAngle;
    update();
}
