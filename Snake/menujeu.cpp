#include "menujeu.h"

MenuJeu::MenuJeu(QWidget *parent, bool joueur2) : QGraphicsView(parent)
{
    scene= new QGraphicsScene(0,0,QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height(),this);
    this->setScene(scene);//associe scene et cette object
    scene->setBackgroundBrush(QBrush(QColor(50,50,50)));

    QGraphicsTextItem* titre = new QGraphicsTextItem("SNAKE");
    scene->addItem(titre);
    titre->setScale(10);
    titre->setPos(scene->width()/3,scene->height()/6);


    GraphicsBouton* jouer= new GraphicsBouton();
    scene->addItem(jouer);
    jouer->setColor(QColor(80,80,80,150));
    jouer->setText("Jouer");
    jouer->setTaille(QRectF(0,0,150,50));
    jouer->setPos(-(jouer->boundingRect().width()/2)+scene->width()/2,5*scene->height()/10);
    QObject::connect(jouer,SIGNAL(clicked()),this,SLOT(emissionLanceJeu()));

    GraphicsBouton* choixCouleur1= new GraphicsBouton();
    scene->addItem(choixCouleur1);
    choixCouleur1->setColor(QColor(80,80,80,150));
    choixCouleur1->setText("Couleur de depart");
    choixCouleur1->setTaille(QRectF(0,0,150,50));
    choixCouleur1->setPos(-(choixCouleur1->boundingRect().width()/2)+scene->width()/2,6*scene->height()/10);
    QObject::connect(choixCouleur1,SIGNAL(clicked()),this,SLOT(emissionCouleur1()));

    GraphicsBouton* choixCouleur2= new GraphicsBouton();
    scene->addItem(choixCouleur2);
    choixCouleur2->setColor(QColor(80,80,80,150));
    choixCouleur2->setText("Couleur d'arrive");
    choixCouleur2->setTaille(QRectF(0,0,150,50));
    choixCouleur2->setPos(-(choixCouleur2->boundingRect().width()/2)+scene->width()/2,7*scene->height()/10);
    QObject::connect(choixCouleur2,SIGNAL(clicked()),this,SLOT(emissionCouleur2()));

    choixJoueur2= new GraphicsBouton();
    scene->addItem(choixJoueur2);
    choixJoueur2->setColor(QColor(80,80,80,150));
    if(joueur2){
        choixJoueur2->setText("Joueur 2 actif");
    }
    else{
        choixJoueur2->setText("Activer joueur 2");
    }
    choixJoueur2->setTaille(QRectF(0,0,150,50));
    choixJoueur2->setPos(-(choixJoueur2->boundingRect().width()/2)+scene->width()/2,8*scene->height()/10);
    QObject::connect(choixJoueur2,SIGNAL(clicked()),this,SLOT(emissionJoueur2()));

    GraphicsBouton* boutonQuitter = new GraphicsBouton();
    scene->addItem(boutonQuitter);
    boutonQuitter->setText("Quitter");
    boutonQuitter->setColor(QColor(155,155,155,155));
    boutonQuitter->setTaille(QRectF(0,0,190,50));
    boutonQuitter->setPos(-(boutonQuitter->boundingRect().width()/2)+scene->width()/2,9*scene->height()/10);
    QObject::connect(boutonQuitter,SIGNAL(clicked()),qApp,SLOT(quit()));

    serpent = new Serpent(40);
    scene->addItem(serpent);
    serpent->setPos(300,100);
    serpent->setDirection(1);

}

MenuJeu::~MenuJeu(){
    delete scene;
}

void MenuJeu::emissionCouleur1(){
    QColor couleur =QColorDialog::getColor(serpent->getSerpent()[0]->getColor(), this,"Couleur 1");
    emit setCouleur1(couleur);
}

void MenuJeu::emissionCouleur2(){

    QColor couleur;
    if(serpent->getSerpent().size()>=20){
        couleur=serpent->getSerpent()[19]->getColor();
    }
    else{
        afficheErreur("Impossible de recup la couleur serpent trop court","Erreur");
    }
    couleur =QColorDialog::getColor(couleur, this,"Couleur 2");
    emit setCouleur2(couleur);
}

void MenuJeu::emissionJoueur2(){
    int reponse =QMessageBox::question(this,"","Activer le Joueur 2 ?");
    emit setJoueur2(reponse == QMessageBox::Yes);
    if(reponse == QMessageBox::Yes){
        choixJoueur2->setText("Joueur 2 actif");
    }
    else{
        choixJoueur2->setText("Activer joueur 2");
    }
}

void MenuJeu::emissionLanceJeu(){
    emit lanceJeu(1);
}

void MenuJeu:: resizeEvent(QResizeEvent *event){
        QGraphicsView::resizeEvent(event);
        QGraphicsView::fitInView(QGraphicsView::sceneRect(), Qt::KeepAspectRatio);//permet de garder le ratio de taille a la remodif de la taille
    }

Serpent* MenuJeu::getSerpent(){
    return serpent;
}

void MenuJeu::afficheErreur(QString texte, QString titre){
    QMessageBox::about(this,titre,texte);
}
