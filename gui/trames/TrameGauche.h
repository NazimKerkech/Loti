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

#include <string>
//class FenetrePrincipale;
#include "TrameCentrale.h"
#include "../../src/image.h"

using namespace std;

class TrameGauche: public QFrame {
    Q_OBJECT
private:
    QListWidget* _Widget_bibliotheque;
    TrameCentrale* _trameCentrale;
public:
    TrameGauche(vector<Image> bibliotheque, TrameCentrale* trameCentrale, QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameGauche");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameGauche { border: 3px solid black; }");
        // Create a QListWidget to display the list
        _Widget_bibliotheque = new QListWidget(this);

        // Add items from the vector to the QListWidget
        for (const Image image : bibliotheque) {
            //QListWidgetItem *listItem = new QListWidgetItem(QString::fromStdString(image._titre));
            _Widget_bibliotheque->addItem(new QListWidgetItem(QString::fromStdString(image.get_titre())));
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
            qDebug() << "Selected item: " << selectedItem->text();
            cout << selectedItem->text().toStdString()<<endl;
            const string LOTI_DIR(SOURCE_DIR);
            //this->_trameCentrale->update_image(LOTI_DIR + "/dta/"+selectedItem->text().toStdString());
            // Add your code to handle the selected item

        }
    }
};
#endif //TRAMEGAUCHE_H
