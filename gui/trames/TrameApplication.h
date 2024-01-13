//
// Created by thedoctor on 13/01/24.
//

#ifndef TRAMEAPPLICATION_H
#define TRAMEAPPLICATION_H
#include <QVBoxLayout>
#include <QApplication>
#include <QMainWindow>
#include <QFrame>
#include <QHBoxLayout>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <string>
#include <QResizeEvent>
#include <QDebug>
#include "TrameSuperieure.h"
#include "TrameCentrale.h"
#include "TrameGauche.h"
#include "TrameDroite.h"
#include <vector>
#include "../../src/image.h"
using namespace std;
using namespace cv;

class TrameApplication : public QFrame {
    Q_OBJECT

protected:
    TrameSuperieure *trameSup;
    TrameCentrale *tramecentrale;
    TrameGauche *tramegauche;
    TrameDroite *tramedroite;
public:
    TrameApplication(vector<Image> bibliotheque, QWidget *parent = nullptr) : QFrame(parent) {
        // Taille
        this->setFixedSize(500, 400);

        // Initialisation des trames
        this->tramecentrale = new TrameCentrale(this);
        this->trameSup = new TrameSuperieure(this, tramecentrale);
        this->tramegauche = new TrameGauche(bibliotheque, tramecentrale, this);
        this->tramedroite = new TrameDroite(tramecentrale, this);

        //QWidget *centralWidget = new QWidget(this);
        //setCentralWidget(centralWidget);

        QVBoxLayout *vlayout = new QVBoxLayout(this);
        vlayout->setContentsMargins(0, 0, 0, 0);
        vlayout->setSpacing(0);


        vlayout->addWidget(this->trameSup);

        // Partie inferieur
        QFrame* frame_inf = new QFrame();
        QHBoxLayout *layout_inf = new QHBoxLayout();
        layout_inf->setContentsMargins(0, 0, 0, 0);
        layout_inf->setSpacing(0);
        layout_inf->addWidget(tramegauche);
        layout_inf->addWidget(tramecentrale);
        layout_inf->addWidget(tramedroite);
        frame_inf->setLayout(layout_inf);

        vlayout->addWidget(frame_inf);

        //setMinimumSize(QSize(0, 0));
        setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));


    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        QFrame::resizeEvent(event);
        this->trameSup->setFixedHeight(event->size().height() / 10);
        this->trameSup->setFixedWidth(event->size().width());
        this->tramegauche->setFixedWidth(event->size().width()*2/10);
        this->tramedroite->setFixedWidth(event->size().width()*2/10);
    }

};
#endif //TRAMEAPPLICATION_H
