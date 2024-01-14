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
using namespace std;
using namespace cv;

class TrameCentrale : public QFrame {
public:
    TrameCentrale(QWidget *parent = nullptr) : QFrame(parent) {
        setObjectName("TrameCentrale");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameCentrale { border: 3px solid black; }");  // Apply style only to the QFrame
        //this->setStyleSheet("border: 5px solid black;");
        const string LOTI_DIR(SOURCE_DIR);

        imageLabel = new AspectRatioPixmapLabel(this);

        update_image(LOTI_DIR + "/dta/1.jpg");

        QVBoxLayout *frameLayout = new QVBoxLayout(this);
        frameLayout->addWidget(imageLabel);

        //this->setFixedWidth(parent->size().width()*6/10);
        //this->setFixedHeight(parent->size().height() * 5/ 6);
    }
    void update_image(string path) {
        // Load the image using OpenCV
        Mat cvImage = imread(path);

        // Convert OpenCV Mat to Qt QPixmap
        QImage qtImage(cvImage.data, cvImage.cols, cvImage.rows, cvImage.step, QImage::Format_BGR888);
        pixmap = QPixmap::fromImage(qtImage);

        // Set the image on the label
        imageLabel->setPixmap(pixmap);

    }
private:
    QPixmap pixmap;
    AspectRatioPixmapLabel* imageLabel;

};



#endif //TRAMECENTRALE_H
