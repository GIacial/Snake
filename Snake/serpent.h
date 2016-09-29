#ifndef SERPENT_H
#define SERPENT_H

#include <QList>
#include <QObject>
#include <QtWidgets>
#include <math.h>
#include "partieserpent.h"
#include "teteserpent.h"

class Serpent: public QGraphicsWidget
{
    Q_OBJECT
public:
    Serpent(int nbPartie=0,QColor couleurDepart=QColor(255,0,0),QColor couleurArrive=QColor(90,0,0));
    ~Serpent();
    void positionerSerpent();                                       //permet de positioner le serpent apres une action
    bool collisionBordEcran(int tailleX,int tailleY);               //permet de savoir si on entre en collision avec les bord
    bool collisionAvecSoi();                                        //dit si on se mord soit meme
    bool collisionAvecObject(QGraphicsWidget* object);              //dit si on entre en collision avec un object
    int getDirection();
    int getNbBoule();
    QList<PartieSerpent*> getSerpent();
    void ajouterBoule();                                            //agrandi le serpent de 1
    void translationEn(int x,int y);
    void setColoration(QColor couleurDepart=QColor(255,0,0),QColor couleurArrive=QColor(90,0,0));

public slots:
    void setDirection(int newDirection);                            //permet de definir la direction du serpent
    void versLeHaut();
    void versLeBas();
    void versLaDroite();
    void versLaGauche();

signals:
    void erreur(QString texte,QString titre);

private:
    //fonction
  void setColorBoule(PartieSerpent* bouleAcolorier);
  QPointF bougerTeteSerpent(QPointF position);                    //defini le position de la tete
  bool retourVersNb(int& num, int cible,int vitesse=1);
  int getAngle();
  void modificationTrajectoire(int& trajectP,int& trajectS,int cibleP ,int cibleS=0);
    //varaible
  QList<PartieSerpent*> serpent ;
  QRectF* tailleBoule;
  int direction;                                                    //0=>haut 1=>droite 2=>bas 3=>gauche
  int ajoutX,ajoutY;
  bool diminue;                                                     //sert a savoir dans quel direction bouge la couleur
  QColor couleur;                                                   //couleur de la derniere boule
  int decalageR,decalageB,decalageV;
  int compteurDecalageCouleur;
  bool possibleChangerDirection;
};

#endif // SERPENT_H
