#include "serpent.h"

Serpent::Serpent(int nbPartie, QColor couleurDepart, QColor couleurArrive)
{
    tailleBoule= new QRectF(0,0,30,30);
    direction=1;
    couleur = couleurDepart;
    compteurDecalageCouleur=0;
    decalageR=(couleurDepart.red()-couleurArrive.red())/20;
    decalageV=(couleurDepart.green()-couleurArrive.green())/20;
    decalageB=(couleurDepart.blue()-couleurArrive.blue())/20;
    diminue =true;
    ajoutX=tailleBoule->width()/4;
    ajoutY=0;
    possibleChangerDirection=true;

    //tete
    TeteSerpent* tete = new TeteSerpent(tailleBoule,this);
    tete->setPos(0,0);
    tete->setZValue(nbPartie);
    serpent << tete;
    setColorBoule(tete);
    tete->setAngle(getAngle());
    //corps
    for(int i=1; i < nbPartie ; i++){
       PartieSerpent* newBoule = new PartieSerpent(tailleBoule,this);
       newBoule->setPos(-i*(tailleBoule->width()/4),0);
       newBoule->setZValue(nbPartie-i);
       serpent << newBoule;
       setColorBoule(newBoule);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Serpent::~Serpent(){
    delete tailleBoule;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Serpent::collisionBordEcran(int tailleX, int tailleY){
    bool collision =false;
    int i=0;
        collision= !( serpent[i]->pos().x()+tailleBoule->width()<tailleX/2 && serpent[i]->pos().x()>-tailleX/2 && serpent[i]->pos().y()+tailleBoule->height()<tailleY/2 && serpent[i]->pos().y()>-tailleY/2);

    return collision;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Serpent::collisionAvecSoi(){
    bool collision =false;
    for(int i=3 ; i< serpent.size(); i++){//ne pas faire les 3 premier
        collision = collision || ((serpent[i]->pos().x()<serpent[0]->pos().x()+(tailleBoule->width()/2) && serpent[0]->pos().x()<serpent[i]->pos().x()+(tailleBoule->width()/2)) //selon x
                && (serpent[i]->pos().y()<serpent[0]->pos().y()+(tailleBoule->height()/2) && serpent[0]->pos().y()<serpent[i]->pos().y()+(tailleBoule->height()/2)));//selon y
    }
    return collision;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Serpent::collisionAvecObject(QGraphicsWidget *object){
  bool collision = false;
  collision =  (object->pos().x()<serpent[0]->pos().x()+tailleBoule->width() && serpent[0]->pos().x()<object->pos().x()+object->boundingRect().width()) //selon x
                && (object->pos().y()<serpent[0]->pos().y()+tailleBoule->height() && serpent[0]->pos().y()<object->pos().y()+object->boundingRect().height());//selon y
 return collision;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::positionerSerpent(){
    for(int i=serpent.size()-1 ; i>=0 ; i--){
        if(i!=0){
           serpent[i]->setPos(serpent[i-1]->pos()); //prend la position de celle d'avant
        }
        else{
            ((TeteSerpent*)serpent[i])->setAngle(getAngle());
            serpent[i]->setPos(bougerTeteSerpent(serpent[i]->pos()));

        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

QPointF Serpent::bougerTeteSerpent(QPointF position){
   // int ajoutX,ajoutY;
    switch (direction) {
    case 0: modificationTrajectoire(ajoutY,ajoutX,-tailleBoule->height()/4);
        break;
    case 1:modificationTrajectoire(ajoutX,ajoutY,tailleBoule->width()/4);
        break;
    case 2:modificationTrajectoire(ajoutY,ajoutX,tailleBoule->width()/4);
        break;
    case 3:modificationTrajectoire(ajoutX,ajoutY,-tailleBoule->height()/4);
        break;
    default:ajoutX=0; ajoutY=0;
        emit erreur("Direction Incconnu","PROBLEME");
        break;
    }
    position.setX(position.x()+ajoutX);
    position.setY(position.y()+ajoutY);
    possibleChangerDirection=true;  //autorise un changement de ditection
    return position;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Serpent::getDirection(){
    return direction;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::setDirection(int newDirection){
        direction=newDirection;
        possibleChangerDirection=false;

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::versLeHaut(){
    if(this->getDirection()!=2 && possibleChangerDirection){
        this->setDirection(0);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::versLeBas(){
    if(this->getDirection()!=0 && possibleChangerDirection){
        this->setDirection(2);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::versLaDroite(){
    if(this->getDirection()!=3 && possibleChangerDirection){
        this->setDirection(1);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::versLaGauche(){
    if(this->getDirection()!=1 && possibleChangerDirection){
        this->setDirection(3);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::setColorBoule(PartieSerpent *bouleAcolorier){
    if(diminue){
        couleur.setRed(couleur.red()-decalageR);
        couleur.setGreen(couleur.green()-decalageV);
        couleur.setBlue(couleur.blue()-decalageB);
        compteurDecalageCouleur++;
        diminue = compteurDecalageCouleur!=20;
    }
    else{
        couleur.setRed(couleur.red()+decalageR);
        couleur.setGreen(couleur.green()+decalageV);
        couleur.setBlue(couleur.blue()+decalageB);
        compteurDecalageCouleur--;
        diminue = compteurDecalageCouleur==0;
    }
    bouleAcolorier->setColor(couleur);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::ajouterBoule(){
    PartieSerpent* newBoule = new PartieSerpent(tailleBoule,this);
    newBoule->setPos(serpent[serpent.size()-1]->pos());
    setColorBoule(newBoule);
    serpent << newBoule;

    //redefinition des Zpos
    for(int i=0 ; i < serpent.size() ; i++){
       serpent[i]->setZValue(serpent.size()-i);
    }

    tailleBoule->setHeight(30+(serpent.size()/20));
    tailleBoule->setWidth(30+(serpent.size()/20));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Serpent::retourVersNb(int &num, int cible, int vitesse){
    bool atteintNb =false;
for(int i=0 ; i<vitesse ; i++){
    if(num !=cible){
       if(num>cible){//cas sup
           num--;
       }
       else{//cas inf
           num++;
       }
    }
    else{
        atteintNb=true;
    }
 }
    return atteintNb;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Serpent::getNbBoule(){
    return serpent.size();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Serpent::getAngle(){
    int angle=0;
    switch (direction) {
    case 0:angle=0+ajoutX*(45/(tailleBoule->width()/4));

        break;
    case 1:angle=90+ajoutY*(45/(tailleBoule->width()/4));

        break;
    case 2:angle=180-ajoutX*(45/(tailleBoule->width()/4));

        break;
    case 3:angle=270-ajoutY*(45/(tailleBoule->width()/4));

        break;
    default:angle=0;
        break;
    }
    return angle;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::modificationTrajectoire(int &trajectP, int &trajectS, int cibleP, int cibleS){
    trajectP=cibleP;
    retourVersNb(trajectS,cibleS);

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::translationEn(int x, int y){
    int decaX = x-serpent[0]->pos().x();
    int decaY = y-serpent[0]->pos().y();

    for(int i=0 ; i<serpent.size() ;i++){
        serpent[i]->setPos(serpent[i]->pos().x()+decaX,serpent[i]->pos().y()+decaY);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

QList<PartieSerpent*> Serpent::getSerpent(){
    return serpent;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serpent::setColoration(QColor couleurDepart, QColor couleurArrive){
    couleur = couleurDepart;
    compteurDecalageCouleur=0;
    decalageR=(couleurDepart.red()-couleurArrive.red())/20;
    decalageV=(couleurDepart.green()-couleurArrive.green())/20;
    decalageB=(couleurDepart.blue()-couleurArrive.blue())/20;
    diminue =true;

    for(int i=0 ; i<serpent.size(); i++){
        setColorBoule(serpent[i]);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
