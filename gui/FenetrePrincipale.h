//
// Created by thedoctor on 10/01/24.
//

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QVBoxLayout>
#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <opencv2/opencv.hpp>
#include <string>
#include <QResizeEvent>

#include "trames/TrameApplication.h"
#include "trames/TrameAuthentification.h"
#include <vector>
#include "../src/image.h"
using namespace std;
using namespace cv;

class FenetrePrincipale : public QMainWindow {
    Q_OBJECT

protected:
    TrameAuthentification *trameAuthentification;
    TrameApplication *trameApplication;
    vector<Image> _bibliotheque;
public:
    FenetrePrincipale(vector<Image> bibliotheque, QWidget *parent = nullptr) : QMainWindow(parent) {
        // Taille
        _bibliotheque = bibliotheque;
        this->setFixedSize(500, 400);

        // Initialisation des trames
        this->trameApplication = new TrameApplication(bibliotheque);
        this->trameAuthentification = new TrameAuthentification(this);

        setCentralWidget(trameAuthentification);

        setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
        connect(trameAuthentification, &TrameAuthentification::loginSuccess, this, &FenetrePrincipale::onLoginSuccess);
    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        QMainWindow::resizeEvent(event);
        this->trameApplication->setFixedHeight(event->size().height());
        this->trameApplication->setFixedWidth(event->size().width());
    }
    private slots:
    void onLoginSuccess() {
        // Remove the login frame and display the main application frame
        delete trameAuthentification;
        trameAuthentification = nullptr;
        delete trameApplication;
        trameApplication = nullptr;
        // Create and set up your main application frame
        // ...
        this->trameApplication = new TrameApplication(_bibliotheque, this);
        setCentralWidget(trameApplication);


        // Optionally, show the main window
        //show();
    }

};
#endif //FENETREPRINCIPALE_H
