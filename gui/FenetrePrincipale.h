//
// Created by thedoctor on 10/01/24.
//

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#endif //FENETREPRINCIPALE_H
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

class FenetrePrincipale : public QMainWindow {
    Q_OBJECT

public:
    FenetrePrincipale(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Create a label to display the image
        const string LOTI_DIR(SOURCE_DIR);
        QLabel *imageLabel = new QLabel(this);

        // Load the image using OpenCV
        cv::Mat cvImage = cv::imread(LOTI_DIR + "/dta/1.jpg");

        // Convert OpenCV Mat to Qt QPixmap
        QImage qtImage(cvImage.data, cvImage.cols, cvImage.rows, cvImage.step, QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(qtImage);

        // Set the image on the label
        imageLabel->setPixmap(pixmap);

        // Set the label as the central widget of the main window
        setCentralWidget(imageLabel);
    }
};