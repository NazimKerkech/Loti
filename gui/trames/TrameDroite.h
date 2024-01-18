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
#include "../../src/biblio.h"
//#include "RescalingPixmapLabel.h"

using namespace std;

class TrameDroite: public QFrame {
    Q_OBJECT
private:
    QListWidget* _Widget_traitementImg;
    QTabWidget* _onglets_histogramme;
    Biblio _bibliotheque;

    signals:
        void traitement(QString traitement);
public:
    TrameDroite(Biblio bibliotheque, QWidget *parent = nullptr) : QFrame(parent) {
        this->_bibliotheque = bibliotheque;
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
