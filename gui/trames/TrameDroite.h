//
// Created by thedoctor on 12/01/24.
//

#ifndef TRAMEDROITE_H
#define TRAMEDROITE_H
#include <QString>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>

#include <string>
//class FenetrePrincipale;
#include "TrameCentrale.h"
#include "../../src/image.h"

using namespace std;

class TrameDroite: public QFrame {
    Q_OBJECT
private:
    QListWidget* _Widget_traitementImg;
    TrameCentrale* _trameCentrale;
public:
    TrameDroite(TrameCentrale* trameCentrale, QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameDroite");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameDroite { border: 3px solid black; }");
        this->setFixedWidth(parent->size().width()*2/10);

        //thomy :
        _Widget_traitementImg = new QListWidget(this);
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Flouter l'image")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Detection de contours")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Detection de lignes droites")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Réaussement de contours")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Segmentation")));

    }
    
};
#endif //TRAMEDROITE_H
