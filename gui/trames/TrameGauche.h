//
// Created by thedoctor on 12/01/24.
//

#ifndef TRAMEGAUCHE_H
#define TRAMEGAUCHE_H
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

#include <string>
//class FenetrePrincipale;
#include "TrameCentrale.h"
#include "../../src/image.h"
#include "../../src/biblio.h"
using namespace std;

class TrameGauche: public QFrame {
    Q_OBJECT
public:
    QListWidget* _Widget_bibliotheque;
    signals:
        void demande_changer_image(int indice_selectionne);
public:
    TrameGauche(Biblio bibliotheque, QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameGauche");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameGauche { border: 3px solid black; }");
        // Create a QListWidget to display the list
        _Widget_bibliotheque = new QListWidget(this);

        // Add items from the vector to the QListWidget
        for (const Image image : bibliotheque.get_images()) {

            //init tableau
            QTableWidget* tableau = new QTableWidget();
            tableau->setRowCount(5);
            tableau->setColumnCount(1);

            // Remplir le tableau avec des données de démonstration
            /*
            tableau->setItem(0, 0, new QTableWidgetItem(QString("Source")));
            tableau->setItem(1, 0, new QTableWidgetItem(QString("Titre")));
            tableau->setItem(2, 0, new QTableWidgetItem(QString("Numéro")));
            tableau->setItem(3, 0, new QTableWidgetItem(QString("Cout")));
            tableau->setItem(4, 0, new QTableWidgetItem(QString("Acces")));
            */
            const int col = 0;
            tableau->setItem(0, col, new QTableWidgetItem(QString(image.get_source().c_str())));
            tableau->setItem(1, col, new QTableWidgetItem(QString(image.get_titre().c_str())));
            tableau->setItem(2, col, new QTableWidgetItem(QString(to_string(image.get_numero()).c_str())));
            tableau->setItem(3, col, new QTableWidgetItem(QString(to_string(image.get_cout()).c_str())));
            tableau->setItem(4, col, new QTableWidgetItem(QString(image.get_acces())));

            //QListWidgetItem *listItem = new QListWidgetItem(QString::fromStdString(image._titre));
            //_Widget_bibliotheque->addItem(new QListWidgetItem(QString::fromStdString(image.get_titre())));
            
            tableau->horizontalHeader()->setVisible(false);
            tableau->setVerticalHeaderLabels(QString("Source;Titre;Numero;Cout;Acces").split(";"));
            tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            QSize tableSize = tableau->sizeHint();
            QListWidgetItem* listWidgetItem = new QListWidgetItem();
            
            tableSize.setHeight(tableau->rowHeight(0) * tableau->rowCount()+5);
            listWidgetItem->setSizeHint(tableSize);
            //listWidgetItem->setSizeHint(tableau->sizeHintForColumn(0) + QSize(5, 5));
                       

            _Widget_bibliotheque->addItem(listWidgetItem);
            _Widget_bibliotheque->setItemWidget(listWidgetItem, tableau);
        }
        connect(_Widget_bibliotheque, &QListWidget::itemSelectionChanged, this, &TrameGauche::onItemSelectionChanged);
        // Set up layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(_Widget_bibliotheque);

        this->setFixedWidth(parent->size().width()*2/10);
        //this->setFixedHeight(parent->size().height() * 5/ 6);

    }
    void onItemSelectionChanged() {
        // This function will be called when an item is selected in the QListWidget
        QListWidgetItem *selectedItem = _Widget_bibliotheque->currentItem();

        if (selectedItem) {
            emit demande_changer_image(_Widget_bibliotheque->row(selectedItem));
        }
    }
};
#endif //TRAMEGAUCHE_H
