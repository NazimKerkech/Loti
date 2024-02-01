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
#include <ctime>
#include <string>
#include "QRangeSlider.hpp"
//class FenetrePrincipale;
#include "TrameCentrale.h"
#include "../../src/image.h"
#include "../../src/biblio.h"
#include "../../src/utilisateur.h"
#include <QLineEdit>
#include <QFileDialog>
#include <filesystem>
#include <cmath>
using namespace std;
namespace fs = std::filesystem;


class TrameGauche: public QFrame {
    Q_OBJECT
public:
    QListWidget* _Widget_bibliotheque;
    QRangeSlider* slider_prix;
    QLabel *prix_min, *prix_max;
    QLineEdit *recherche_saisie;
    QLineEdit *source_edit, *titre_edit, *cout_edit, *numero_edit, *acces_edit;
    string id;
    Biblio _bibliotheque, _bibliothequeStoquee;
    QTableWidget* _tableau;

    signals:
        void demande_changer_image(int indice_selectionne);
        void nouvelle_bibliotheque(Biblio bibliotheque);
        //void majTableau(int row, int column, string text, int indice);
        
public:
    TrameGauche(Biblio bibliotheque, string id, QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameGauche");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameGauche { border: 3px solid black; }");
        // Create a QListWidget to display the list
        _Widget_bibliotheque = new QListWidget(this);
        this->id = id;
        _bibliotheque = bibliotheque;
        _bibliothequeStoquee = bibliotheque;
        // Add items from the vector to the QListWidget
        int indice = 0;
        std::unordered_map<int, QString> initialValues;
        for ( Image image : bibliotheque.get_images()) {

            const string LOTI_DIR(SOURCE_DIR);
            Utilisateur user;
            user.loadCSV(LOTI_DIR + "/dta/utilisateurs.txt");

            user.login(id);
            string access = user.getUserAccess();
            if (user.getUserAccess() == "2" || image.get_acces() == 'L') {

                //init tableau

                QTableWidget* _tableau = new QTableWidget();
                _tableau->setRowCount(5);
                _tableau->setColumnCount(1);
                // Remplir le tableau avec des donn�es de d�monstration
                /*
                tableau->setItem(0, 0, new QTableWidgetItem(QString("Source")));
                tableau->setItem(1, 0, new QTableWidgetItem(QString("Titre")));
                tableau->setItem(2, 0, new QTableWidgetItem(QString("Num�ro")));
                tableau->setItem(3, 0, new QTableWidgetItem(QString("Cout")));
                tableau->setItem(4, 0, new QTableWidgetItem(QString("Acces")));
                */
                const int col = 0;
                _tableau->setItem(0, col, new QTableWidgetItem(QString(image.get_source().c_str())));
                _tableau->setItem(1, col, new QTableWidgetItem(QString(image.get_titre().c_str())));
                _tableau->setItem(2, col, new QTableWidgetItem(QString(to_string(image.get_numero()).c_str())));
                _tableau->setItem(3, col, new QTableWidgetItem(QString(to_string(image.get_cout()).c_str())));
                _tableau->setItem(4, col, new QTableWidgetItem(QString(image.get_acces())));

                _tableau->item(2, col)->setFlags(_tableau->item(2, col)->flags() & ~Qt::ItemIsEditable);

                if(user.getUserAccess() == "1") {
                    _tableau->item(0, col)->setFlags(_tableau->item(0, col)->flags() & ~Qt::ItemIsEditable);
                    _tableau->item(1, col)->setFlags(_tableau->item(1, col)->flags() & ~Qt::ItemIsEditable);
                    _tableau->item(3, col)->setFlags(_tableau->item(3, col)->flags() & ~Qt::ItemIsEditable);
                    _tableau->item(4, col)->setFlags(_tableau->item(4, col)->flags() & ~Qt::ItemIsEditable);
                }
                //maj des valeurs dans la base de donne si modification
                connect(_tableau, &QTableWidget::cellChanged, this, &TrameGauche::maj_tableau);

                //QListWidgetItem *listItem = new QListWidgetItem(QString::fromStdString(image._titre));
                //_Widget_bibliotheque->addItem(new QListWidgetItem(QString::fromStdString(image.get_titre())));

                _tableau->setSelectionMode(QAbstractItemView::NoSelection);
                _tableau->horizontalHeader()->setVisible(false);
                _tableau->setVerticalHeaderLabels(QString("Source;Titre;Numero;Cout;Acces").split(";"));
                _tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

                QSize tableSize = _tableau->sizeHint();
                QListWidgetItem* listWidgetItem = new QListWidgetItem();

                tableSize.setHeight(_tableau->rowHeight(0) * _tableau->rowCount() + 5);
                listWidgetItem->setSizeHint(tableSize);
                //listWidgetItem->setSizeHint(tableau->sizeHintForColumn(0) + QSize(5, 5));


                _Widget_bibliotheque->addItem(listWidgetItem);
                _Widget_bibliotheque->setItemWidget(listWidgetItem, _tableau);

                
            }
            indice++;

        }
        connect(_Widget_bibliotheque, &QListWidget::itemSelectionChanged, this, &TrameGauche::onItemSelectionChanged);

        // Set up layout

        slider_prix = new QRangeSlider(this);
        slider_prix->setLowValue(floor(this->_bibliotheque.getPrixMin()));
        slider_prix->setHighValue(int(ceil(this->_bibliotheque.getPrixMax())));
        slider_prix->setRange(floor(this->_bibliotheque.getPrixMin()), int(ceil(this->_bibliotheque.getPrixMax())));

        prix_min = new QLabel(QString::fromStdString(to_string(int(floor(this->_bibliotheque.getPrixMin())))));
        prix_max = new QLabel(QString::fromStdString(to_string(int(ceil(this->_bibliotheque.getPrixMax())))));
        this->prix_min->setText(QString::fromStdString(to_string(int(floor(slider_prix->lowValue())))));
        this->prix_max->setText(QString::fromStdString(to_string(int(ceil(slider_prix->highValue())))));

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

        QPushButton *trier = new QPushButton("trie decroissant");
        connect(trier, &QPushButton::clicked, this, &TrameGauche::trie);

        recherche_saisie = new QLineEdit(this);

        layout->addWidget(recherche_saisie);
        layout->addWidget(prix_frame);
        layout->addWidget(chercher);
        layout->addWidget(trier);
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
    public slots:
    void maj_tableau(int row, int column) {//()[_tableau, indice, this]
        QListWidgetItem *selectedItem = _Widget_bibliotheque->currentItem();
        int indice = _Widget_bibliotheque->row(selectedItem);

        QListWidgetItem* item1 = _Widget_bibliotheque->item(indice);
        QTableWidget* tableau = dynamic_cast<QTableWidget*>(_Widget_bibliotheque->itemWidget(item1));
        QTableWidgetItem* item = tableau->item(row, column);

        if (item) {
            qDebug() << "Cell changed at" << row << "," << column << "New value:" << item->text();
            //majTableau(row, column, item->text().toStdString(), indice);
            //QTableWidgetItem* newItem = new QTableWidgetItem("New Value");
            string text = item->text().toStdString();
            std::istringstream iss(text);
            string premierMot;

            QString newValue = "New Value";
            switch (row) {
            case 0:

                iss >> premierMot;

                // Nouvelle valeur à mettre dans la cellule
                item->setText(QString::fromStdString(premierMot));
                (*this->_bibliotheque.get_imagespointer())[indice].set_source(premierMot);
                break;
            case 1:
                (*this->_bibliotheque.get_imagespointer())[indice].set_titre(text);
                break;
            case 2:
                try {
                    size_t pos = 0;
                    std::stoi(item->text().toStdString(), &pos);
                    if (pos == text.size()) {
                        //_bibliotheque.get_imagespointer()[indice].set_numero(text);
                    }
                    else {
                        cout << "Ce n'est pas completement un entier";
                        time_t now = time(0);
                        item->setText(QString::fromStdString(to_string(now)));
                        //_bibliotheque.get_images()[indice].set_numero(to_string(now));
                    }
                }
                catch (...) {
                    cout << "Ce n'est pas un entier"; // La conversion a échoué
                    time_t now = time(0);
                    item->setText(QString::fromStdString(to_string(now)));
                    //_bibliotheque.get_images()[indice].set_numero(to_string(now));

                }
                break;
            case 3:
                try {
                    size_t pos = 0;
                    std::stod(item->text().toStdString(), &pos);
                    if (pos == text.size()) {
                        (*_bibliotheque.get_imagespointer())[indice].set_cout(text);;
                    }
                    else {
                        cout << "Ce n'est pas completement un nombre reel";
                        item->setText("0.0");
                        (*_bibliotheque.get_imagespointer())[indice].set_cout("0.0");
                    }
                }
                catch (...) {
                    cout << "Ce n'est pas un nombre reel"; // La conversion a échoué
                    item->setText("0.0");
                    (*_bibliotheque.get_imagespointer())[indice].set_numero("0.0");
                }

                break;
            case 4:
                if ((item->text().toStdString()[0] == 'L') || (item->text().toStdString()[0] == 'R'))
                {
                    (*_bibliotheque.get_imagespointer())[indice].set_acces(text);
                    item->setText(QString(item->text().toStdString()[0]));
                }
                else
                {
                    (*_bibliotheque.get_imagespointer())[indice].set_acces("R");
                    item->setText("R");
                }
                break;
            default:
                qDebug() << "Erreur maj valeur tableau" << endl;
                break;
            }
            this->charge_biblio(_bibliotheque);
            emit this->nouvelle_bibliotheque(_bibliotheque);
            this->charger_biblio_externe(_bibliotheque);
        }
    }

    void enregistere_bib(string path) {
        this->_bibliotheque.sauvgarder(path);
    }
    void ajouter_image() {
        const string LOTI_DIR(SOURCE_DIR);
        const string DATA_DIR(LOTI_DIR+"/dta/");
        QFileDialog *dialogue = new QFileDialog();
        QString file_name = dialogue->getOpenFileName(this, "ouvrir une bibliotheque", QString::fromStdString(DATA_DIR), tr("Images (*.png *.jpg *.bmp *.tif *.tiff *.jpeg)"));

        string fichier = file_name.toStdString();
        if (fichier==""){
            return;
        }
        std::filesystem::path pathObj(fichier);
        std::string fileNameWithoutExtension = pathObj.stem().string();

        std::hash<std::string> hasher;  // Hash function for strings
        time_t now = time(0); // unique id
        string numeroImage = to_string(now);
        vector<string> descripteurs;
        std::istringstream iss(source_edit->text().toStdString());
        string premierMot;
        iss >> premierMot;
        descripteurs.push_back(premierMot);
        descripteurs.push_back(titre_edit->text().toStdString());
        descripteurs.push_back(numeroImage);
        string text = cout_edit->text().toStdString();
        try {
            size_t pos = 0;
            std::stod(text, &pos);
            if (pos == text.size()) {
                descripteurs.push_back(cout_edit->text().toStdString());
            }
            else {
                cout << "Ce n'est pas completement un nombre reel";
                descripteurs.push_back("0.00");
            }
        }
        catch (...) {
            cout << "Ce n'est pas un nombre reel"; // La conversion a échoué
            descripteurs.push_back("0.00");
        }

        if ((acces_edit->text().toStdString()[0] == 'L') || (acces_edit->text().toStdString()[0] == 'R'))
        {
            descripteurs.push_back(acces_edit->text().toStdString());
        }
        else
        {
            descripteurs.push_back("R");
        }
        

        std::filesystem::path pathObj2(fichier);
        std::string extension = pathObj2.extension().string();
        std::filesystem::copy_file(fichier, DATA_DIR+numeroImage+extension, std::filesystem::copy_options::overwrite_existing);

        Image nouvelle_img = Image(descripteurs);
        this->_bibliotheque.ajouter_image(nouvelle_img);
        this->_bibliotheque.updateCSV();
        this->charge_biblio(_bibliotheque);
        emit this->nouvelle_bibliotheque(_bibliotheque);
    }
    void charge_biblio(Biblio bibliotheque) {
        this->_bibliotheque = bibliotheque;
        //this->_bibliothequeStoquee = bibliotheque;
        _Widget_bibliotheque->clear();
        int indice = 0;
        for (const Image image : bibliotheque.get_images()) {

            const string LOTI_DIR(SOURCE_DIR);
            Utilisateur user;
            user.loadCSV(LOTI_DIR + "/dta/utilisateurs.txt");

            user.login(id);
            string access = user.getUserAccess();
            if (user.getUserAccess() == "2" || image.get_acces() == 'L') {

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

                tableau->item(2, col)->setFlags(tableau->item(2, col)->flags() & ~Qt::ItemIsEditable);

                if(user.getUserAccess() == "1") {
                    tableau->item(0, col)->setFlags(tableau->item(0, col)->flags() & ~Qt::ItemIsEditable);
                    tableau->item(1, col)->setFlags(tableau->item(1, col)->flags() & ~Qt::ItemIsEditable);
                    tableau->item(3, col)->setFlags(tableau->item(3, col)->flags() & ~Qt::ItemIsEditable);
                    tableau->item(4, col)->setFlags(tableau->item(4, col)->flags() & ~Qt::ItemIsEditable);
                }
                //maj des valeurs dans la base de donne si modification
                connect(tableau, &QTableWidget::cellChanged, this, &TrameGauche::maj_tableau);

                tableau->setSelectionMode(QAbstractItemView::NoSelection);
                tableau->horizontalHeader()->setVisible(false);
                tableau->setVerticalHeaderLabels(QString("Source;Titre;Numero;Cout;Acces").split(";"));
                tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

                QSize tableSize = tableau->sizeHint();
                QListWidgetItem* listWidgetItem = new QListWidgetItem();

                tableSize.setHeight(tableau->rowHeight(0) * tableau->rowCount() + 5);
                listWidgetItem->setSizeHint(tableSize);

                _Widget_bibliotheque->addItem(listWidgetItem);
                _Widget_bibliotheque->setItemWidget(listWidgetItem, tableau);
            }
            indice++;
        }
        slider_prix->setLowValue(int(floor(this->_bibliothequeStoquee.getPrixMin())));
        slider_prix->setHighValue(int(ceil(this->_bibliothequeStoquee.getPrixMax())));
        slider_prix->setRange(int(floor(this->_bibliothequeStoquee.getPrixMin())), int(ceil(this->_bibliothequeStoquee.getPrixMax())));
        this->prix_min->setText(QString::fromStdString(to_string(int(floor(slider_prix->lowValue())))));
        this->prix_max->setText(QString::fromStdString(to_string(int(ceil(slider_prix->highValue())))));
    }
    void charger_biblio_externe(Biblio bib) {
        _bibliothequeStoquee = bib;
    }
    void trie() {
        //_bibliotheque = _bibliothequeStoquee;
        this->_bibliotheque.trier();
        this->charge_biblio(this->_bibliotheque);
        emit charge_biblio(this->_bibliotheque);
    }
    void slide_prix() {
        this->prix_min->setText(QString::fromStdString(to_string(int(floor(slider_prix->lowValue())))));
        this->prix_max->setText(QString::fromStdString(to_string(int(ceil(slider_prix->highValue())))));
    }
    void onItemSelectionChanged() {
        // This function will be called when an item is selected in the QListWidget
        QListWidgetItem *selectedItem = _Widget_bibliotheque->currentItem();

        int c = _bibliotheque.get_images().size();
        if (selectedItem) {
            if (_Widget_bibliotheque->row(selectedItem) < _bibliotheque.get_images().size()) {
                emit demande_changer_image(_Widget_bibliotheque->row(selectedItem));
            }
        }
    }
    void chercher() {
        string num = this->recherche_saisie->text().toStdString();
        int numero = stoi((num=="") ? "0" : num);
        double prix_min = slider_prix->lowValue();
        double prix_max = slider_prix->highValue();
        string source = "";
        _bibliotheque = _bibliothequeStoquee.filterImages(source, numero, prix_min, prix_max);
        this->charge_biblio(_bibliotheque);
        emit nouvelle_bibliotheque(_bibliotheque);
    }
};
#endif //TRAMEGAUCHE_H
