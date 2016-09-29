#include "interfacejeux.h"

InterfaceJeux::InterfaceJeux(int tailleX, int tailleY, QWidget *parent, QColor couleurDepart, QColor couleurArrive,bool activerJ2):QGraphicsView(parent)
{
//creation scene
    plateauHauteur=tailleY;
    plateauLargeur=tailleX;
    scene= new QGraphicsScene(-200-(tailleX/2), -tailleY/2, 200+tailleX, tailleY,this);
    this->setScene(scene);//associe scene et cette object
    scene->setBackgroundBrush(QBrush(QColor(50,50,50)));
//creation serpent
    //j1
    Serpent* s = new Serpent(30,couleurDepart,couleurArrive);
    s->positionerSerpent();
    scene->addItem(s);
    s->setPos(0,0);
    QObject::connect(s,SIGNAL(erreur(QString,QString)),this,SLOT(afficheErreur(QString,QString)));
    joueur << s;

    //j2
    if(activerJ2){
        setJoueurS(QColor(255-couleurDepart.red(),255-couleurDepart.green(),255-couleurDepart.blue()),QColor(255-couleurArrive.red(),255-couleurArrive.green(),255-couleurArrive.blue()));
    }
//bouton quiter
    boutonQuitter = new GraphicsBouton();
    scene->addItem(boutonQuitter);
    boutonQuitter->setText("Quitter");
    boutonQuitter->setColor(QColor(155,155,155,155));
    boutonQuitter->setTaille(QRectF(0,0,190,50));
    boutonQuitter->setPos(-200-(tailleX/2),(tailleY/2)-boutonQuitter->boundingRect().height());
    QObject::connect(boutonQuitter,SIGNAL(clicked()),qApp,SLOT(quit()));

//creation chrono
    chrono = new QTimer(this);
    chrono->setInterval(100);
    chrono->setSingleShot(false);
    QObject::connect(chrono,SIGNAL(timeout()),this,SLOT(deplacementSerpent()));
//cadre
    QPolygon cadre ;
    cadre.append(QPoint(-tailleX/2,-tailleY/2));
    cadre.append(QPoint(-tailleX/2,tailleY/2));
    cadre.append(QPoint(tailleX/2,tailleY/2));
    cadre.append(QPoint(tailleX/2,-tailleY/2));
    scene->addPolygon(cadre,QPen(QColor(255,255,255,255)));
 //pomme
    taillePomme=new QRectF(0,0,15,15);
   ajoutPomme();
    //les textes
   textePause = new QGraphicsTextItem("PAUSE");
   scene->addItem(textePause);
   textePause->setScale(1+(tailleX/100));
   textePause->setPos(-tailleX/4,-tailleY/5);
   textePause->setDefaultTextColor(QColor(255,255,255));
   textePause->hide();
for(int i=0 ;i<joueur.size() ;i++){
   texteScore << new QGraphicsTextItem("J"+QString::number(i+1)+" Taille :"+QString::number(joueur[i]->getNbBoule()));
   scene->addItem(texteScore[i]);
   texteScore[i]->setScale(3);
   texteScore[i]->setPos(-200-(tailleX/2),(50*i)-(tailleY/2));
   texteScore[i]->setDefaultTextColor(QColor(255,255,255));
}
   //raccouci cla  vier
       QShortcut* haut = new QShortcut(Qt::Key_Z,this);
       QObject::connect(haut,SIGNAL(activated()),joueur[0],SLOT(versLeHaut()));

       QShortcut* bas = new QShortcut(Qt::Key_S,this);
       QObject::connect(bas,SIGNAL(activated()),joueur[0],SLOT(versLeBas()));

       QShortcut* gauche = new QShortcut(Qt::Key_Q,this);
       QObject::connect(gauche,SIGNAL(activated()),joueur[0],SLOT(versLaGauche()));

       QShortcut* droite = new QShortcut(Qt::Key_D,this);
       QObject::connect(droite,SIGNAL(activated()),joueur[0],SLOT(versLaDroite()));

       pause = new QShortcut(Qt::Key_P,this);
       QObject::connect(pause,SIGNAL(activated()),this,SLOT(Mettrepause()));


    //fin
    chrono->start();

}

InterfaceJeux::~InterfaceJeux(){
    delete scene;                     //detruit aussi tout les object qui ont ete mis dedans
    delete chrono;                     //mes destructeur des autre objet fait tout planter
    delete taillePomme;
    //detruit aussi tout ce qui est lie par un this
}

void InterfaceJeux::afficheErreur(QString texte, QString titre){
    QMessageBox::about(this,titre,texte);
}

void InterfaceJeux::deplacementSerpent(){
   for(int i=0 ;i<joueur.size();i++){
    joueur[i]->positionerSerpent();
    verifCollision(i);
   }
}




void InterfaceJeux::mettrePomme(int i){
    int pommeX =rand()%((int)(plateauLargeur-40)/2);
    int pommeY =rand()%((int)(plateauHauteur-40)/2);
    if(rand()%100 <50){
        pommeX*=-1;
    }
    if(rand()%100 <50){
        pommeY*=-1;
    }
    pomme[i]->setPos(pommeX,pommeY);
}

void InterfaceJeux:: resizeEvent(QResizeEvent *event){
        QGraphicsView::resizeEvent(event);
        QGraphicsView::fitInView(QGraphicsView::sceneRect(), Qt::KeepAspectRatio);//permet de garder le ratio de taille a la remodif de la taille
    }

void InterfaceJeux::ajoutPomme(){
    pomme << new Pomme(taillePomme);
    pomme[pomme.size()-1]->setColor(QColor(255,50,50));
    scene->addItem(pomme[pomme.size()-1]);
    pomme[pomme.size()-1]->setZValue(0);
    mettrePomme(pomme.size()-1);
}

void InterfaceJeux::Mettrepause(){
    if((!chrono->isActive())){
        //QObject::connect(chrono,SIGNAL(timeout()),this,SLOT(deplacementSerpent()));       //connection
        chrono->start();
        textePause->hide();
        scene->setForegroundBrush(QBrush(QColor(0,0,0,0)));
    }
    else{
        //QObject::disconnect(chrono,SIGNAL(timeout()),this,SLOT(deplacementSerpent()));    //deconnection
        chrono->stop();
        textePause->show();
        scene->setForegroundBrush(QBrush(QColor(0,0,0,180)));
    }
}

void InterfaceJeux::verifCollision(int j){
    if(joueur[j]->collisionBordEcran(plateauLargeur,plateauHauteur) || collisionEntreSerpent(j)){
        textePause->setPlainText("JOUEUR "+QString::number(j+1)+" A PERDU");
        textePause->setPos(-scene->width()/2,textePause->pos().y());
        QObject::disconnect(pause,SIGNAL(activated()),this,SLOT(Mettrepause()));
        Mettrepause();
        chrono->setInterval(5000);
        QObject::disconnect(chrono,SIGNAL(timeout()),this,SLOT(deplacementSerpent()));    //deconnection
        QObject::connect(chrono,SIGNAL(timeout()),this,SLOT(retourAuTitre()));    //connection
        chrono->start();
    }
    else{
        for(int i=0 ; i<pomme.size() ;i++){
         if(joueur[j]->collisionAvecObject(pomme[i])){
            mettrePomme(i);
            joueur[j]->ajouterBoule();
            texteScore[j]->setPlainText("J"+QString::number(j+1)+" Taille :"+QString::number(joueur[j]->getNbBoule()));
            if(rand()%100<5){
                ajoutPomme();
            }
         }
        }
    }
}

bool InterfaceJeux::collisionEntreSerpent(int i){
    QList<PartieSerpent*> serpent;
    bool collision =false;
    for(int j=0 ; j<joueur.size() ; j++){
        if(j!=i ){
            serpent = joueur[j]->getSerpent();
            for(int k=0; k<serpent.size() ; k++){
                collision= collision || joueur[i]->collisionAvecObject(serpent[k]);
            }
        }
        else{
            collision = collision || joueur[i]->collisionAvecSoi();
        }
    }
    return collision;
}

void InterfaceJeux::setJoueurS( QColor couleurDepart, QColor couleurArrive){
    Serpent* joueurS = new Serpent(30,couleurDepart,couleurArrive);
    joueurS->positionerSerpent();
    scene->addItem(joueurS);
    joueurS->setPos(0,0);
    joueurS->translationEn(0,50);
    QObject::connect(joueurS,SIGNAL(erreur(QString,QString)),this,SLOT(afficheErreur(QString,QString)));
    joueur << joueurS;

    //raccourci clavier
    QShortcut* haut = new QShortcut(Qt::Key_Up,this);
    QObject::connect(haut,SIGNAL(activated()),joueur[1],SLOT(versLeHaut()));

    QShortcut* bas = new QShortcut(Qt::Key_Down,this);
    QObject::connect(bas,SIGNAL(activated()),joueur[1],SLOT(versLeBas()));

    QShortcut* gauche = new QShortcut(Qt::Key_Left,this);
    QObject::connect(gauche,SIGNAL(activated()),joueur[1],SLOT(versLaGauche()));

    QShortcut* droite = new QShortcut(Qt::Key_Right,this);
    QObject::connect(droite,SIGNAL(activated()),joueur[1],SLOT(versLaDroite()));
}

void InterfaceJeux::retourAuTitre(){
    emit finJeu(2);
}
