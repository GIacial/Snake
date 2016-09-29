#ifndef BOULE_H
#define BOULE_H

#include <QGraphicsWidget>
#include <QObject>
#include <QColor>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <math.h>
class Boule: public QGraphicsWidget
{
    Q_OBJECT
public:
    Boule(QRectF* tailleBoule, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;//sert a determiner la taille de l'object
    QPainterPath shape() const;//determine la zone cliquable
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);//style graphics de item
    QColor getColor()const;//renvoi la couleur de la boule
    void setColor(QColor couleur);//permet de mettre une couleur a la boule



signals:

public slots:


protected:
    QColor color;//couleurs de la boule
    QRectF* taille;
};

#endif // BOULE_H
