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
#include "../../src/image.h"

using namespace std;
using namespace cv;

class TrameCentrale : public QFrame {
private:
    vector<Image> bibliotheque;
    Image _image;
public:
    TrameCentrale(vector<Image> bibliotheque, QWidget *parent = nullptr) : QFrame(parent) {
        this->bibliotheque = bibliotheque;
        setObjectName("TrameCentrale");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameCentrale { border: 3px solid black; }");  // Apply style only to the QFrame
        //this->setStyleSheet("border: 5px solid black;");
        const string LOTI_DIR(SOURCE_DIR);

        imageLabel = new AspectRatioPixmapLabel(this);
        _image = bibliotheque[0];
        update_image(_image);

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
            this->update_image(bibliotheque[indice_selectionne]);
        }
        void appliquer_traitement(QString traitement) {
            cout << traitement.toStdString()<<endl;
            if(traitement.toStdString()=="Flouter l'image") {
                //Mat filtre = (Mat_<float>(3, 3) <<  1, 0, 1, 0, -4, 0, 1, 0, 1);
                //cout << filtre <<endl;
                Mat filtre = Mat(5, 5, CV_32F, Scalar(1))/25;
                cout << filtre <<endl;

                Mat convoluee = _image.convolution(filtre);
                QImage qtImage(convoluee.data, convoluee.cols, convoluee.rows, convoluee.step, QImage::Format_BGR888);
                pixmap = QPixmap::fromImage(qtImage);
                // Set the image on the label
                imageLabel->setPixmap(pixmap);
            }
        }
private:
    QPixmap pixmap;
    AspectRatioPixmapLabel* imageLabel;

};



#endif //TRAMECENTRALE_H
