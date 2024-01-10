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
const string DATA_DIR(LOTI_DIR+"/dta/");

int main(int argc, char* argv[]) 
{
       
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hello there ;)" << std::endl;
    cout << "Ol Korect !" <<endl;

    cout << "Ahmed !" <<endl;

    cout << "heeeeyy" << endl;
    cout << "heeeeyy" << endl;

    vector<vector<string>> data;
    cout << DATA_DIR + "descripteurs.csv" << endl;
    data = loadCSV(DATA_DIR + "descripteurs.csv");
    cout << data.size()<<endl;
    vector<Image> Bibliotheque;
    Bibliotheque = createBib(data);

    //affichage des descripteurs :
    Bibliotheque[0].afficheDescripteurs();
    Bibliotheque[1].afficheDescripteurs();

    //modification d'un descripteur d'une image :
    data[1][0] = "DallE_2";
    writeCSV(DATA_DIR + "descripteurs.csv", data);

    //affichage des images :
    //Bibliotheque[0].afficheImage();
    //Bibliotheque[1].afficheImage();

    //recuperer un pixel d'une image et le nombre de lignes et do colonnes
    cout << "Valeur pixel : " << Bibliotheque[2].BGR(1000, 2000) << endl;
    cout << "Taille x : " << Bibliotheque[2].rows() << endl;
    cout << "Taille y : " << Bibliotheque[2].cols() << endl;

    //Hough
    //Bibliotheque[0].houghLineTransform();

    //convolution
    Mat filtre = Mat(3, 3, CV_8UC3, Scalar(1,1,1));
    std::cout << filtre;

    Mat convoluee = Bibliotheque[0].convolution(filtre);
    Bibliotheque[0].afficheImage();
    //Ajouter une image a la base de donnee
    addImage("C:/Users/etudiant/Downloads/image.png");
    
    cv::waitKey(0); //Laisser les fenetres ouvertes

    //////// Test Qt //////////
    /*
    QApplication a(argc, argv);
    // Read an image using OpenCV
    cv::Mat cvImage = cv::imread(LOTI_DIR + "/dta/1.jpg");

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
    */
    return 0;
}
