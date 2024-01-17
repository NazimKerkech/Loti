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

public:
    TrameSuperieure *trameSup;
    TrameCentrale *tramecentrale;
    TrameGauche *tramegauche;
    TrameDroite *tramedroite;
public:
    TrameApplication(vector<Image> bibliotheque, QWidget *parent = nullptr) : QFrame(parent) {
        // Taille
        this->setFixedSize(500, 400);

        // Initialisation des trames
        this->tramecentrale = new TrameCentrale(bibliotheque, this);
        this->trameSup = new TrameSuperieure(this);
        this->tramegauche = new TrameGauche(bibliotheque, this);
        this->tramedroite = new TrameDroite(bibliotheque, this);

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

        bool connected1 = connect(this->tramegauche, &TrameGauche::demande_changer_image, this->tramecentrale, &TrameCentrale::changer_image);
        bool connected2 = connect(this->tramegauche, &TrameGauche::demande_changer_image, this->tramedroite, &TrameDroite::charger_histogramme);
        bool connected3 = connect(this->tramedroite, &TrameDroite::traitement, this->tramecentrale, &TrameCentrale::appliquer_traitement);

        //connect(trameApplication->tramegauche, &TrameGauche::demande_changer_image, trameApplication->tramecentrale, &TrameCentrale::changer_image);
        if (!connected1 || !connected2 || !connected3) {
            qDebug() << "Failed to connect the signal and slot!";
        }
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
