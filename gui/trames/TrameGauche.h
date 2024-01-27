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
#include "QRangeSlider.hpp"
//class FenetrePrincipale;
#include "TrameCentrale.h"
#include "../../src/image.h"
#include "../../src/biblio.h"
#include <QLineEdit>
#include <QFileDialog>
#include <filesystem>
using namespace std;

class TrameGauche: public QFrame {
    Q_OBJECT
public:
    QListWidget* _Widget_bibliotheque;
    QRangeSlider* slider_prix;
    QLabel *prix_min, *prix_max;
    QLineEdit *recherche_saisie;
    QLineEdit *source_edit, *titre_edit, *cout_edit, *numero_edit, *acces_edit;
    string id;
    Biblio _bibliotheque;
    signals:
        void demande_changer_image(int indice_selectionne);
        void nouvelle_bibliotheque(Biblio bibliotheque);
public:
    TrameGauche(Biblio bibliotheque, string id, QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameGauche");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameGauche { border: 3px solid black; }");
        // Create a QListWidget to display the list
        _Widget_bibliotheque = new QListWidget(this);
        this->id = id;
        _bibliotheque = bibliotheque;

        // Add items from the vector to the QListWidget
        for (const Image image : bibliotheque.get_images()) {

            //init tableau
            QTableWidget* tableau = new QTableWidget();
            tableau->setRowCount(5);
            tableau->setColumnCount(1);

            // Remplir le tableau avec des donn�es de d�monstration
            /*
            tableau->setItem(0, 0, new QTableWidgetItem(QString("Source")));
            tableau->setItem(1, 0, new QTableWidgetItem(QString("Titre")));
            tableau->setItem(2, 0, new QTableWidgetItem(QString("Num�ro")));
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

            tableau->setSelectionMode(QAbstractItemView::NoSelection);
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

        slider_prix = new QRangeSlider(this);
        slider_prix->setLowValue(0);
        slider_prix->setHighValue(100);
        slider_prix->setRange(0, 100);

        prix_min = new QLabel("0");
        prix_max = new QLabel("100");
        connect(slider_prix, &QRangeSlider::lowValueChange, this, &TrameGauche::slide_prix);
        connect(slider_prix, &QRangeSlider::highValueChange, this, &TrameGauche::slide_prix);


        QVBoxLayout *layout = new QVBoxLayout(this);

        QHBoxLayout *prix_layout = new QHBoxLayout();
        prix_layout->addWidget(prix_min);
        prix_layout->addWidget(slider_prix);
        prix_layout->addWidget(prix_max);
        QFrame *prix_frame = new QFrame();
        prix_frame->setLayout(prix_layout);

        QPushButton *chercher = new QPushButton("chercher");
        connect(chercher, &QPushButton::clicked, this, &TrameGauche::chercher);

        recherche_saisie = new QLineEdit(this);

        layout->addWidget(recherche_saisie);
        layout->addWidget(prix_frame);
        layout->addWidget(chercher);
        layout->addWidget(_Widget_bibliotheque);

        const string LOTI_DIR(SOURCE_DIR);
        Utilisateur user;
        user.loadCSV(LOTI_DIR+"/dta/utilisateurs.txt");

        user.login(id);
        string access = user.getUserAccess();
        if(user.getUserAccess() == "2") {
            QPushButton *ajouterImg = new QPushButton("Ajouter une image");
            connect(ajouterImg, &QPushButton::clicked, this, &TrameGauche::ajouter_image);

            QFrame *frame_add_img = new QFrame(this);
            QGridLayout *layout_add_img = new QGridLayout();
            layout_add_img->addWidget(new QLabel("Source"), 0, 0);
            this->source_edit = new QLineEdit(this);
            layout_add_img->addWidget(source_edit, 0, 1);

            layout_add_img->addWidget(new QLabel("Titre"), 0, 2);
            this->titre_edit = new QLineEdit(this);
            layout_add_img->addWidget(titre_edit, 0, 3);

            layout_add_img->addWidget(new QLabel("Cout"), 1, 0);
            this->cout_edit = new QLineEdit(this);
            layout_add_img->addWidget(cout_edit, 1, 1);

            layout_add_img->addWidget(new QLabel("Acces"), 1, 2);
            this->acces_edit = new QLineEdit(this);
            layout_add_img->addWidget(acces_edit, 1, 3);

            frame_add_img->setLayout(layout_add_img);

            layout->addWidget(frame_add_img);
            layout->addWidget(ajouterImg);

            this->setFixedWidth(parent->size().width()*2/10);
            //this->setFixedHeight(parent->size().height() * 5/ 6);
        }

    }
    void ajouter_image() {
        const string LOTI_DIR(SOURCE_DIR);
        const string DATA_DIR(LOTI_DIR+"/dta/");
        QFileDialog *dialogue = new QFileDialog();
        QString file_name = dialogue->getOpenFileName(this, QString::fromStdString(DATA_DIR), tr("Bibliotheque (*.bib)"));
        string fichier = file_name.toStdString();

        std::filesystem::path pathObj(fichier);
        std::string fileNameWithoutExtension = pathObj.stem().string();


        vector<string> descripteurs;
        descripteurs.push_back(source_edit->text().toStdString());
        descripteurs.push_back(titre_edit->text().toStdString());
        descripteurs.push_back(fileNameWithoutExtension);
        descripteurs.push_back(cout_edit->text().toStdString());
        descripteurs.push_back(acces_edit->text().toStdString());
        Image nouvelle_img = Image(descripteurs);
        this->_bibliotheque.ajouter_image(nouvelle_img, fichier);
        this->_bibliotheque.updateCSV();
        this->charge_biblio(_bibliotheque);
        emit nouvelle_bibliotheque(_bibliotheque);
    }
    void charge_biblio(Biblio bibliotheque) {
        this->_bibliotheque = bibliotheque;
        _Widget_bibliotheque->clear();
        for (const Image image : bibliotheque.get_images()) {

            //init tableau
            QTableWidget* tableau = new QTableWidget();
            tableau->setRowCount(5);
            tableau->setColumnCount(1);
            const int col = 0;
            tableau->setItem(0, col, new QTableWidgetItem(QString(image.get_source().c_str())));
            tableau->setItem(1, col, new QTableWidgetItem(QString(image.get_titre().c_str())));
            tableau->setItem(2, col, new QTableWidgetItem(QString(to_string(image.get_numero()).c_str())));
            tableau->setItem(3, col, new QTableWidgetItem(QString(to_string(image.get_cout()).c_str())));
            tableau->setItem(4, col, new QTableWidgetItem(QString(image.get_acces())));

            tableau->setSelectionMode(QAbstractItemView::NoSelection);
            tableau->horizontalHeader()->setVisible(false);
            tableau->setVerticalHeaderLabels(QString("Source;Titre;Numero;Cout;Acces").split(";"));
            tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            QSize tableSize = tableau->sizeHint();
            QListWidgetItem* listWidgetItem = new QListWidgetItem();

            tableSize.setHeight(tableau->rowHeight(0) * tableau->rowCount()+5);
            listWidgetItem->setSizeHint(tableSize);

            _Widget_bibliotheque->addItem(listWidgetItem);
            _Widget_bibliotheque->setItemWidget(listWidgetItem, tableau);
        }
    }
    void slide_prix() {
        this->prix_min->setText(QString::fromStdString(to_string(slider_prix->lowValue())));
        this->prix_max->setText(QString::fromStdString(to_string(slider_prix->highValue())));
    }
    void onItemSelectionChanged() {
        // This function will be called when an item is selected in the QListWidget
        QListWidgetItem *selectedItem = _Widget_bibliotheque->currentItem();

        if (selectedItem) {
            emit demande_changer_image(_Widget_bibliotheque->row(selectedItem));
        }
    }
    void chercher() {
        string code = this->recherche_saisie->text().toStdString();
        int prix_min = slider_prix->lowValue();
        int prix_max = slider_prix->highValue();
        //chercher
    }
};
#endif //TRAMEGAUCHE_H
