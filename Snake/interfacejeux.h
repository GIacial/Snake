#ifndef INTERFACEJEUX_H
#define INTERFACEJEUX_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets>
#include "serpent.h"
#include "pomme.h"
#include "graphicsbouton.h"


class InterfaceJeux : public QGraphicsView
{
    Q_OBJECT
public:
    InterfaceJeux(int tailleX, int tailleY, QWidget* parent=0, QColor couleurDepart=QColor(255,0,0), QColor couleurArrive=QColor(90,0,0), bool activerJ2=false);
    ~InterfaceJeux();

signals:
    void finJeu(int);
public slots:
    void afficheErreur(QString texte,QString titre);//slots qui affiche le texte en pparametre
    void deplacementSerpent();                      //on deplace le serpent une fois
    void Mettrepause();
    void retourAuTitre();

protected:
    void resizeEvent(QResizeEvent *event);//def comment reagie l'object au changement de taille

private:
    //fonction
    void mettrePomme(int i);
    void ajoutPomme();
    void verifCollision(int j);
    bool collisionEntreSerpent(int i);
    void setJoueurS( QColor couleurDepart=QColor(255,0,0), QColor couleurArrive=QColor(90,0,0));
    //varaible
    QGraphicsScene* scene;
    QList<Serpent*> joueur;
    QTimer* chrono;                     //timer entre 2 action
    QList<Boule*> pomme;
    QRectF* taillePomme;
    QGraphicsTextItem* textePause;
    QList<QGraphicsTextItem*> texteScore;
    int plateauLargeur,plateauHauteur;
    QShortcut* pause;
    GraphicsBouton* boutonQuitter;


};

#endif // INTERFACEJEUX_H
