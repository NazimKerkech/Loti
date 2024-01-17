//
// Created by thedoctor on 12/01/24.
//
#ifndef TRAMESUPERIEURE_H
#define TRAMESUPERIEURE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include <string>
//class FenetrePrincipale;
#include "TrameCentrale.h"

using namespace std;

class TrameSuperieure : public QFrame {
    Q_OBJECT
public:
    TrameSuperieure(QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameSuperieure");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameSuperieure { border: 3px solid black; }");

        QHBoxLayout *vlayout = new QHBoxLayout(this);

        QPushButton* bouton = new QPushButton("hallo!");
        connect(bouton, &QPushButton::clicked, this, &TrameSuperieure::onButtonClicked);
        vlayout->addWidget(bouton);

        this->setFixedWidth(parent->size().width());
        this->setFixedHeight(parent->size().height() / 10);
    }
    private slots:
    void onButtonClicked() {
    }

};

#endif //TRAMESUPERIEURE_H
