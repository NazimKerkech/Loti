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
    QTabWidget* _onglets_histogramme;
    signals:
        void traitement(QString traitement);
public:
    TrameDroite(QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameDroite");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameDroite { border: 3px solid black; }");
        //this->setFixedWidth(parent->size().width()*2/10);

        //thomy :
        _Widget_traitementImg = new QListWidget(this);
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Flouter l'image")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Detection de contours")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Detection de lignes droites")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Rehaussement de contours")));
        _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Segmentation")));

        connect(_Widget_traitementImg, &QListWidget::itemDoubleClicked, this, &TrameDroite::onItemDoubleClicked);


        _onglets_histogramme = new QTabWidget(this);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(_Widget_traitementImg);
        layout->addStretch();
        layout->addWidget(_onglets_histogramme);

        this->setFixedWidth(parent->size().width()*2/10);
    }
public:
    void onItemDoubleClicked() {
        QListWidgetItem *selectedItem = _Widget_traitementImg->currentItem();

        if (selectedItem) {
            cout<<"application des traitements ..."<<endl;
            emit traitement(selectedItem->text());
        }
    }
};
#endif //TRAMEDROITE_H
