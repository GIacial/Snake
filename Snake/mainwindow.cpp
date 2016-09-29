#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    numFenetre=0;
    jeu=NULL;
    menuDujeu=NULL;
    couleur1=QColor(50,150,255);
    couleur2=QColor(50,50,155);
    joueur2=false;


    allerFenetre(2);
}

MainWindow::~MainWindow()
{
   // delete jeu;
}

void MainWindow::allerFenetre(int numFen){
 //destruction de l'ancienne fenetre
    //les destruction on l'air d'etre fait lorsqu'on appel setCentralWidget
 //construction de la prochaine
    numFenetre=numFen;
    switch (numFenetre) {
    case 1: jeu = new InterfaceJeux(QApplication::desktop()->screenGeometry().width()-200,QApplication::desktop()->screenGeometry().height(),this,couleur1,couleur2,joueur2);
        setCentralWidget(jeu);
        QObject::connect(jeu,SIGNAL(finJeu(int)),this,SLOT(allerFenetre(int)));
        break;
    case 2://creation menu principal
        menuDujeu= new MenuJeu(this,joueur2);
        menuDujeu->getSerpent()->setColoration(couleur1,couleur2);
        setCentralWidget(menuDujeu);
        QObject::connect(menuDujeu,SIGNAL(lanceJeu(int)),this,SLOT(allerFenetre(int)));
        QObject::connect(menuDujeu,SIGNAL(setCouleur1(QColor)),this,SLOT(setCouleur1(QColor)));
        QObject::connect(menuDujeu,SIGNAL(setCouleur2(QColor)),this,SLOT(setCouleur2(QColor)));
        QObject::connect(menuDujeu,SIGNAL(setJoueur2(bool)),this,SLOT(setJoueur2(bool)));
        break;
    default:
        break;
    }
}

void MainWindow::setCouleur1(QColor couleur){
    couleur1=couleur;
    menuDujeu->getSerpent()->setColoration(couleur1,couleur2);
}

void MainWindow::setCouleur2(QColor couleur){
    couleur2=couleur;
    menuDujeu->getSerpent()->setColoration(couleur1,couleur2);
}

void MainWindow::setJoueur2(bool active){
    joueur2=active;
}
