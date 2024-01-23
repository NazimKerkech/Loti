//
// Created by thedoctor on 12/01/24.
//

#ifndef TRAMECENTRALE_H
#define TRAMECENTRALE_H
#include <QLabel>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <string>
#include <QResizeEvent>
#include <QDebug>
#include <QPainter>
#include "AspectRatioPixmapLabel.h"
#include <QString>
#include <QVBoxLayout>
#include "../../src/image.h"
#include "../../src/biblio.h"

using namespace std;
using namespace cv;

class TrameCentrale : public QFrame {
    Q_OBJECT
    Biblio bibliotheque;
    Image _image;
    int _indice;
    signals:
        void c_nouvelle_bibliotheque(Biblio bibliotheque);
public:
    TrameCentrale(Biblio bibliotheque, QWidget *parent = nullptr) : QFrame(parent) {
        this->bibliotheque = bibliotheque;
        setObjectName("TrameCentrale");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameCentrale { border: 3px solid black; }");  // Apply style only to the QFrame
        //this->setStyleSheet("border: 5px solid black;");
        const string LOTI_DIR(SOURCE_DIR);

        imageLabel = new AspectRatioPixmapLabel(this);
        //_image = bibliotheque[0];
        //update_image(_image);

        QVBoxLayout *frameLayout = new QVBoxLayout(this);
        frameLayout->addWidget(imageLabel);

    }
    void update_image(Image img) {
        _image = img;
        Mat image = img.getImg();

        // Convert OpenCV Mat to Qt QPixmap
        QImage qtImage(image.data, image.cols, image.rows, image.step, QImage::Format_BGR888);
        pixmap = QPixmap::fromImage(qtImage);

        // Set the image on the label
        imageLabel->setPixmap(pixmap);
    }
    public slots:
        void changer_image(int indice_selectionne) {
            _indice = indice_selectionne;
            this->update_image(bibliotheque.get_images()[indice_selectionne]);
        }
        void flouter(int taille_filtre) {
            Mat filtre = Mat(taille_filtre, taille_filtre, CV_32F, Scalar(1))/(taille_filtre*taille_filtre);
            //cout << filtre <<endl;

            Mat resultat = _image.convolution(filtre);
            Mat resultat2;
            normalize(resultat, resultat2, 0, 255, NORM_MINMAX);

            QImage qtImage(resultat2.data, resultat2.cols, resultat2.rows, resultat2.step, QImage::Format_BGR888);
            pixmap = QPixmap::fromImage(qtImage);
            // Set the image on the label
            imageLabel->setPixmap(pixmap);
        }
        void deriver(int noFiltre) {
            Mat resultat = _image.laplacien(noFiltre);
            Mat resultat2;
            normalize(resultat, resultat2, 0, 255, NORM_MINMAX);

            QImage qtImage(resultat2.data, resultat2.cols, resultat2.rows, resultat2.step, QImage::Format_BGR888);
            pixmap = QPixmap::fromImage(qtImage);
            // Set the image on the label
            imageLabel->setPixmap(pixmap);
        }
        void detecter_lignes() {
            Mat resultat = _image.houghLineTransform();
            Mat resultat2;
            normalize(resultat, resultat2, 0, 255, NORM_MINMAX);

            QImage qtImage(resultat2.data, resultat2.cols, resultat2.rows, resultat2.step, QImage::Format_BGR888);
            pixmap = QPixmap::fromImage(qtImage);
            // Set the image on the label
            imageLabel->setPixmap(pixmap);
        }
        void rehausser(int noFiltre) {
            Mat resultat = _image.rehaussementContour(noFiltre);
            Mat resultat2;
            normalize(resultat, resultat2, 0, 255, NORM_MINMAX);

            QImage qtImage(resultat2.data, resultat2.cols, resultat2.rows, resultat2.step, QImage::Format_BGR888);
            pixmap = QPixmap::fromImage(qtImage);
            // Set the image on the label
            imageLabel->setPixmap(pixmap);
        }
        void segmenter(int seuil_r, int seuil_g, int seuil_b) {
            Mat resultat = _image.Segmentation(seuil_r, seuil_g, seuil_b);
            Mat resultat2;
            normalize(resultat, resultat2, 0, 255, NORM_MINMAX);

            QImage qtImage(resultat2.data, resultat2.cols, resultat2.rows, resultat2.step, QImage::Format_BGR888);
            pixmap = QPixmap::fromImage(qtImage);
            // Set the image on the label
            imageLabel->setPixmap(pixmap);
        }
        void appliquer_traitement(QString traitement) {
            cout << traitement.toStdString()<<endl;
            if(traitement.toStdString()=="Flouter l'image") {
                //Mat filtre = (Mat_<float>(3, 3) <<  1, 0, 1, 0, -4, 0, 1, 0, 1);
                //cout << filtre <<endl;
                Mat filtre = Mat(5, 5, CV_32F, Scalar(1))/25;
                //cout << filtre <<endl;

                Mat resultat = _image.convolution(filtre);
                Mat resultat2;
                normalize(resultat, resultat2, 0, 255, NORM_MINMAX);

                QImage qtImage(resultat2.data, resultat2.cols, resultat2.rows, resultat2.step, QImage::Format_BGR888);
                pixmap = QPixmap::fromImage(qtImage);
                // Set the image on the label
                imageLabel->setPixmap(pixmap);
            }
        }
        void charge_biblio(Biblio bibliotheque) {
            this->bibliotheque = bibliotheque;
        }
        void suprimer_image() {
            this->bibliotheque.delImage2(bibliotheque.get_images()[_indice].get_numero());
            emit c_nouvelle_bibliotheque(this->bibliotheque);
        }
private:
    QPixmap pixmap;
    AspectRatioPixmapLabel *imageLabel;

};



#endif //TRAMECENTRALE_H
