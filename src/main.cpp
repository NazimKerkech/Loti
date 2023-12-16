#include <iostream>
#include <vector>
#include "image.h"

#include <QCoreApplication>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QApplication>

using namespace std;

const string LOTI_DIR(SOURCE_DIR);

int main(int argc, char* argv[]) 
{
       
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hello there ;)" << std::endl;
    cout << "Ol Korect !" <<endl;

    cout << "Ahmed !" <<endl;

    cout << "heeeeyy" << endl;
    cout << "heeeeyy" << endl;

    vector<vector<string>> data;
    cout << LOTI_DIR + "/dta/descripteurs.csv" << endl;
    data = loadCSV(LOTI_DIR+"/dta/descripteurs.csv");
    cout << data.size()<<endl;
    vector<Image> Bibliotheque;
    Bibliotheque = createBib(data);

    Bibliotheque[0].afficheDescripteurs();
    Bibliotheque[1].afficheDescripteurs();

    data[1][0] = "DallE_2";
    writeCSV(LOTI_DIR + "/dta/descripteurs.csv", data);

    QApplication a(argc, argv);
    // Read an image using OpenCV
    cv::Mat cvImage = cv::imread(LOTI_DIR + "/dta/ico1.jpg");

    // Convert OpenCV image to QImage
    QImage qtImage(cvImage.data, cvImage.cols, cvImage.rows, cvImage.step, QImage::Format_RGB888);

    // Set up the main window
    QMainWindow mainWindow;
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // Create a QLabel to display the image
    QLabel* label = new QLabel(centralWidget);
    label->setPixmap(QPixmap::fromImage(qtImage));

    // Add the QLabel to the layout
    layout->addWidget(label);
    mainWindow.setCentralWidget(centralWidget);

    // Show the main window
    mainWindow.show();

    return a.exec();
}
