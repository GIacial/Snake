#ifndef MENUJEU_H
#define MENUJEU_H

#include <QWidget>
#include <QGraphicsView>
#include <QtWidgets>
#include "graphicsbouton.h"
#include "serpent.h"

class MenuJeu : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MenuJeu(QWidget *parent = 0,bool joueur2=false);
    ~MenuJeu();
    Serpent* getSerpent();

signals:
    void lanceJeu(int);
    void setCouleur1(QColor);
    void setCouleur2(QColor);
    void setJoueur2(bool);

public slots:
    void emissionCouleur1();
    void emissionCouleur2();
    void emissionJoueur2();
    void emissionLanceJeu();
    void afficheErreur(QString texte, QString titre);

protected:
    void resizeEvent(QResizeEvent *event);//def comment reagie l'object au changement de taille

private:
    QGraphicsScene* scene;
    GraphicsBouton* choixJoueur2;
    Serpent* serpent;

};

#endif // MENUJEU_H
