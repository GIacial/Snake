#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfacejeux.h"
#include "menujeu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void setCouleur1(QColor couleur);
    void setCouleur2(QColor couleur);
    void setJoueur2(bool active);
    void allerFenetre(int numFen);
private:
    //fonction

    //variable
    InterfaceJeux* jeu;
    MenuJeu* menuDujeu;
    int numFenetre;
    QColor couleur1;
    QColor couleur2;
    bool joueur2;
};

#endif // MAINWINDOW_H
