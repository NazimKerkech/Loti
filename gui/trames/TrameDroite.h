//
// Created by thedoctor on 12/01/24.
//

#ifndef TRAMEDROITE_H
#define TRAMEDROITE_H
#include <QString>
#include <QTreeWidget>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFrame>
#include <string>
//class FenetrePrincipale;
#include "TrameCentrale.h"
#include "../../src/image.h"
#include "../../src/biblio.h"
#include "../../src/utilisateur.h"
//#include "RescalingPixmapLabel.h"

using namespace std;

class TrameDroite: public QFrame {
    Q_OBJECT
private:
    QTreeWidget* _Widget_traitementImg;
    QTabWidget* _onglets_histogramme;
    Biblio _bibliotheque;

    QSpinBox *SpinBox_flou_taille;
    QSlider *seuil_r, *seuil_g, *seuil_b;
    QLabel *seuilr_label, *seuilg_label, *seuilb_label;

    signals:
        void flou(int taille_filtre);
        void contours(int noFiltre);
        void traitement(QString traitement);
        void detection_lignes();
        void rehaussement();
        void segmentation(int seuil_r, int seuil_g, int seuil_b);
public:
    TrameDroite(Biblio bibliotheque, string id, QWidget *parent = nullptr) : QFrame(parent) {
        this->_bibliotheque = bibliotheque;
        setObjectName("TrameDroite");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameDroite { border: 3px solid black; }");
        //this->setFixedWidth(parent->size().width()*2/10);

        //thomy :
        _Widget_traitementImg = new QTreeWidget();
        _Widget_traitementImg->setHeaderLabels(QString("Traitement d'image").split(";"));

        // FLOUTER L'IMAGE
        QTreeWidgetItem *flouter_Item = new QTreeWidgetItem(_Widget_traitementImg);
        flouter_Item->setText(0, QString::fromStdString("Flouter l'image"));

        QLabel *taille = new QLabel("Taille du filtre");
        this->SpinBox_flou_taille = new QSpinBox;
        SpinBox_flou_taille->setRange(3, 9);
        SpinBox_flou_taille->setSingleStep(2);
        QPushButton *appliquer_flou = new QPushButton("Appliquer");
        connect(appliquer_flou, &QPushButton::clicked, this, &TrameDroite::onflou);

        QGridLayout *flou_layout = new QGridLayout;
        flou_layout->addWidget(taille, 0, 0);
        flou_layout->addWidget(SpinBox_flou_taille, 0, 1);
        flou_layout->addWidget(appliquer_flou, 1, 1);

        QFrame *flou_frame = new QFrame;
        flou_frame->setLayout(flou_layout);

        QTreeWidgetItem *flouter_Options = new QTreeWidgetItem(flouter_Item);
        _Widget_traitementImg->setItemWidget(flouter_Options, 0, flou_frame);

        // DETECTION DE CONTOURS
        QTreeWidgetItem *contours_Item = new QTreeWidgetItem(_Widget_traitementImg);
        contours_Item->setText(0, QString::fromStdString("Detection de contours"));

        QPushButton *appliquer_contours = new QPushButton("Appliquer");
        connect(appliquer_contours, &QPushButton::clicked, this, &TrameDroite::onContours);

        QGridLayout *contours_layout = new QGridLayout;
        contours_layout->addWidget(appliquer_contours, 1, 1);
        QFrame *contours_frame = new QFrame;
        contours_frame->setLayout(contours_layout);
        QTreeWidgetItem *contours_Options = new QTreeWidgetItem(contours_Item);
        _Widget_traitementImg->setItemWidget(contours_Options, 0, contours_frame);

        // DETECTION DE LIGNES DROITES
        QTreeWidgetItem *lignes_Item = new QTreeWidgetItem(_Widget_traitementImg);
        lignes_Item->setText(0, QString::fromStdString("Detection de lignes droites"));

        QPushButton *appliquer_lignes = new QPushButton("Appliquer");
        connect(appliquer_lignes, &QPushButton::clicked, this, &TrameDroite::onLignes);

        QGridLayout *lignes_layout = new QGridLayout;
        lignes_layout->addWidget(appliquer_lignes, 1, 1);
        QFrame *lignes_frame = new QFrame;
        lignes_frame->setLayout(lignes_layout);
        QTreeWidgetItem *lignes_Options = new QTreeWidgetItem(lignes_Item);
        _Widget_traitementImg->setItemWidget(lignes_Options, 0, lignes_frame);

        // REHAUSSEMENT DE CONTOURS
        QTreeWidgetItem *rehauss_Item = new QTreeWidgetItem(_Widget_traitementImg);
        rehauss_Item->setText(0, QString::fromStdString("Rehaussement de contours"));

        QPushButton *appliquer_rehauss = new QPushButton("Appliquer");
        connect(appliquer_rehauss, &QPushButton::clicked, this, &TrameDroite::onRehauss);

        QGridLayout *rehauss_layout = new QGridLayout;
        rehauss_layout->addWidget(appliquer_rehauss, 1, 1);
        QFrame *rehauss_frame = new QFrame;
        rehauss_frame->setLayout(rehauss_layout);
        QTreeWidgetItem *rehauss_Options = new QTreeWidgetItem(rehauss_Item);
        _Widget_traitementImg->setItemWidget(rehauss_Options, 0, rehauss_frame);

        // SEGMENTATION
        QTreeWidgetItem *seg_Item = new QTreeWidgetItem(_Widget_traitementImg);
        seg_Item->setText(0, QString::fromStdString("Segmentation"));

        seuil_r = new QSlider(Qt::Horizontal);
        seuil_r->setRange(0, 255);
        seuil_r->setMinimumSize(50, 0);
        seuil_g = new QSlider(Qt::Horizontal);
        seuil_g->setRange(0, 255);
        seuil_g->setMinimumSize(50, 0);
        seuil_b = new QSlider(Qt::Horizontal);
        seuil_b->setRange(0, 255);
        seuil_b->setMinimumSize(50, 0);

        //seuil->setTickPosition(QSlider::TicksAbove);
        seuilr_label = new QLabel();
        seuilg_label = new QLabel();
        seuilb_label = new QLabel();

        connect(seuil_r, &QSlider::valueChanged, this, &TrameDroite::slide);
        connect(seuil_g, &QSlider::valueChanged, this, &TrameDroite::slide);
        connect(seuil_b, &QSlider::valueChanged, this, &TrameDroite::slide);

        QPushButton *appliquer_seg = new QPushButton("Appliquer");
        connect(appliquer_seg, &QPushButton::clicked, this, &TrameDroite::onSegmentation);

        QGridLayout *seg_layout = new QGridLayout;
        seg_layout->addWidget(new QLabel("rouge"), 0, 0);
        seg_layout->addWidget(seuil_r, 0, 1);
        seg_layout->addWidget(seuilr_label, 0, 2);
        seg_layout->addWidget(new QLabel("vert"), 1, 0);
        seg_layout->addWidget(seuil_g, 1, 1);
        seg_layout->addWidget(seuilg_label, 1, 2);
        seg_layout->addWidget(new QLabel("bleu"), 2, 0);
        seg_layout->addWidget(seuil_b, 2, 1);
        seg_layout->addWidget(seuilb_label, 2, 2);

        seg_layout->addWidget(appliquer_seg, 3, 2);
        QFrame *seg_frame = new QFrame;
        seg_frame->setLayout(seg_layout);
        QTreeWidgetItem *seg_Options = new QTreeWidgetItem(seg_Item);
        _Widget_traitementImg->setItemWidget(seg_Options, 0, seg_frame);

            /*_Widget_traitementImg = new QListWidget();
            _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Flouter l'image")));
            _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Detection de contours")));
            _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Detection de lignes droites")));
            _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Rehaussement de contours")));
            _Widget_traitementImg->addItem(new QListWidgetItem(QString::fromStdString("Segmentation")));

            connect(_Widget_traitementImg, &QListWidget::itemDoubleClicked, this, &TrameDroite::onItemDoubleClicked);*/

        _onglets_histogramme = new QTabWidget(this);

        QVBoxLayout *layout = new QVBoxLayout(this);

        const string LOTI_DIR(SOURCE_DIR);
        Utilisateur user;
        user.loadCSV(LOTI_DIR+"/dta/utilisateurs.txt");

        user.login(id);
        string access = user.getUserAccess();
        if(user.getUserAccess() == "2") {
            layout->addWidget(_Widget_traitementImg);
        }
        layout->addStretch();
        layout->addWidget(_onglets_histogramme);

        this->setFixedWidth(parent->size().width()*2/10);
    }
public:
    void onflou() {
        emit flou(SpinBox_flou_taille->value());
    }
    void onContours() {
        emit contours(2);
    }
    void onLignes() {
        emit detection_lignes();
    }
    void onRehauss() {
        emit rehaussement();
    }
    void onSegmentation() {
        emit segmentation(seuil_r->value(), seuil_g->value(), seuil_b->value());
    }
    void onItemDoubleClicked() {
        //QListWidgetItem *selectedItem = _Widget_traitementImg->currentItem();
        QTreeWidgetItem *selectedItem = _Widget_traitementImg->currentItem();
        if (selectedItem) {
            cout<<"application des traitements ..."<<endl;
            emit traitement(selectedItem->text(0));
        }
    }
    void slide() {
        seuilr_label->setText(QString::fromStdString(to_string(seuil_r->value())));
        seuilg_label->setText(QString::fromStdString(to_string(seuil_g->value())));
        seuilb_label->setText(QString::fromStdString(to_string(seuil_b->value())));
    }
    public slots:
    void charger_histogramme(int indice_selectionne) {
        auto histograms = this->_bibliotheque.get_images()[indice_selectionne].histogramme();
        Mat histImageBlue = std::get<0>(histograms);
        Mat histImageGreen = std::get<1>(histograms);
        Mat histImageRed = std::get<2>(histograms);
        Mat histImage = std::get<3>(histograms);

        string hists[4] = {"R", "G", "B", "Gris"};
        Mat histogrammes[4] = {histImageRed, histImageGreen, histImageBlue, histImage};
        _onglets_histogramme->clear();

        AspectRatioPixmapLabel* imageLabel;
        for(int i=0; i<4; i++) {
            imageLabel = new AspectRatioPixmapLabel(this);
            imageLabel->setPixmap(get_pixmap(histogrammes[i]));
            _onglets_histogramme->addTab(imageLabel, QString::fromStdString(hists[i]));
        }
    }
    QPixmap get_pixmap(Mat image) {
        QPixmap pixmap;
        // Convert OpenCV Mat to Qt QPixmap
        QImage qtImage(image.data, image.cols, image.rows, image.step, QImage::Format_BGR888);
        pixmap = QPixmap::fromImage(qtImage);
        return pixmap;
    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        QFrame::resizeEvent(event);
        _onglets_histogramme->setFixedHeight(event->size().height()*3/10);
    }
};
#endif //TRAMEDROITE_H
