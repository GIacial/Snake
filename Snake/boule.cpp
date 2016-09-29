#include "boule.h"

Boule::Boule(QRectF *tailleBoule, QGraphicsItem *parent):  QGraphicsWidget(parent)
{
       setAcceptHoverEvents(true);//permet d'activer la detection du passage de la souris sur item
       setCacheMode(DeviceCoordinateCache);//def la resolution de l'item
       taille=tailleBoule;
       color=QColor(255,0,0);
}

QRectF Boule::boundingRect() const{
       return *taille;
}

QPainterPath Boule::shape() const{
        QPainterPath path;
        path.addEllipse(boundingRect());//defini la zone cliquable
        return path;
}

void Boule::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){
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

}


QColor Boule::getColor()const{
    return color;
}

void Boule::setColor(QColor couleur){
    color=couleur;
    update();
}
