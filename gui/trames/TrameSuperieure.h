//
// Created by thedoctor on 12/01/24.
//
#ifndef TRAMESUPERIEURE_H
#define TRAMESUPERIEURE_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>

#include <string>
//class FenetrePrincipale;
#include "TrameCentrale.h"
#include "../../src/utilisateur.h"
using namespace std;

class TrameSuperieure : public QFrame {
    Q_OBJECT
private:
    QLabel *iconLabel;
    string id;
    QFileDialog *dialogue;

    signals:
        void nouvelle_bibliotheque(Biblio bibliotheque);
public:
    TrameSuperieure(string id, QWidget *parent = nullptr) : QFrame(parent) {
        this->id = id;
        setObjectName("TrameSuperieure");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameSuperieure { border: 3px solid black; }");

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(10, 10, 10, 10);  // Adjust margins as needed

        // Create the colored disc with user initials
        iconLabel = new QLabel(this);
        iconLabel->setFixedSize(30, 30);  // Adjust size as needed

        updateIcon();

        // Create a label for the user's name
        QLabel *nameLabel = new QLabel(QString::fromStdString(id), this);  // Replace with the user's name
        //nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        //layout->setDirection(QBoxLayout::RightToLeft);
        const string LOTI_DIR(SOURCE_DIR);
        Utilisateur user;
        user.loadCSV(LOTI_DIR+"/dta/utilisateurs.txt");

        user.login(id);
        string access = user.getUserAccess();
        QColor couleur;
        if(user.getUserAccess() == "2") {
            QPushButton *openButton = new QPushButton("Ouvrir une bibliotheque", this);
            connect(openButton, &QPushButton::clicked, this, &TrameSuperieure::openFile);
            layout->addWidget(openButton);
        }
        layout->addStretch();
        layout->addWidget(iconLabel);
        layout->addWidget(nameLabel);
        //layout->addStretch();

        this->dialogue = new QFileDialog();
        //connect(dialogue, &QFileDialog::filesSelected, this, &TrameSuperieure::fichier_selectionne);

        this->setFixedWidth(parent->size().width());
        this->setFixedHeight(parent->size().height() / 10);
    }
    void openFile() {
        //dialogue->open();
        const string LOTI_DIR(SOURCE_DIR);
        const string DATA_DIR(LOTI_DIR+"/dta/");

        QString file_name = dialogue->getOpenFileName(this, QString::fromStdString(DATA_DIR), tr("Image"));
        string fichier = file_name.toStdString();

        Biblio Bibliotheque(fichier);
        emit nouvelle_bibliotheque(Bibliotheque);
        // ouvrir la biblio
    }
    /*void fichier_selectionne() {
        QFileDialog::getOpenFileName();
        QString file_name = dialogue->getOpenFileName();
        cout<<file_name.toStdString()<<endl;
    }*/
    void updateIcon() {
        const string LOTI_DIR(SOURCE_DIR);
        Utilisateur user;
        user.loadCSV(LOTI_DIR+"/dta/utilisateurs.txt");

        user.login(id);
        string access = user.getUserAccess();
        QColor couleur;
        if(user.getUserAccess() == "2") {
            couleur = QColor(Qt::green);
        }
        else {
            couleur = QColor(Qt::red);
        }
        // Function to update the colored disc with user initials
        QPixmap pixmap(20, 20);  // Adjust size as needed
        pixmap.fill(QColor("#00FFFFFF"));  // Replace with the desired color

        QPen pen(couleur);
        pen.setBrush(couleur);  // Set brush color (fill color)
        pen.setColor(QColor(0, 0, 0, 0));  // Set pen color (border color) with alpha 0 for transparency

        QPainter painter(&pixmap);
        painter.setPen(pen);
        painter.setBrush(couleur);
        painter.drawEllipse(0, 0, 10, 10);  // Example: Draw an ellipse

        painter.setRenderHint(QPainter::Antialiasing, true);
        //painter.setBrush(Qt::red);
        //painter.drawEllipse(0, 0, 30, 30);  // Adjust size as needed
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(pixmap.rect(), Qt::AlignCenter, "");

        iconLabel->setPixmap(pixmap);
    }

};

#endif //TRAMESUPERIEURE_H
