#include <iostream>
#include <vector>
#include "image.h"
#include "../gui/FenetrePrincipale.h"

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
    vector<vector<string>> data;
    //cout << DATA_DIR + "descripteurs.csv" << endl;
    data = loadCSV(DATA_DIR + "descripteurs.csv");
    //cout << data.size()<<endl;
    vector<Image> Bibliotheque;
    Bibliotheque = createBib(data);

    /*
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
    */
    //Hough
    //Bibliotheque[0].houghLineTransform();

    //convolution
    /*Mat filtre = Mat(3, 3, CV_32FC3, Scalar(1,1,1))/9;

    cout << filtre;

    Mat convoluee = Bibliotheque[0].convolution(filtre);
    //Bibliotheque[0].afficheImage();
    //imshow("convoluee", convoluee);
    //Ajouter une image a la base de donnee
    

    //addImage("C:/Users/etudiant/Downloads/image.png", "defaut.bib");
    delImage("1", "defaut.bib");
    cv::waitKey(0);*/
    //cv::waitKey(0); //Laisser les fenetres ouvertes

    ////// Laplacien
    ///
    /*  Mat laplacienImage =  Bibliotheque[0].laplacien();
    imshow("Image filtrée", laplacienImage);
    waitKey(0);*/
    //Rehaussement
       Mat imageRehaussee = Bibliotheque[0].rehaussementContour();
       waitKey(0);
    
    //Test de la segmentation
    /*segmentation
    Bibliotheque[0].Segmentation(Bibliotheque[0].getImg(),20,100,200);
    Bibliotheque[0].afficheImage();*/

    auto histograms = Bibliotheque[0].histogramme();
    Mat histImageBlue = std::get<0>(histograms);
    Mat histImageGreen = std::get<1>(histograms);
    Mat histImageRed = std::get<2>(histograms);
    Mat histImage = std::get<3>(histograms);

    //Mat histImageCombined = std::get<4>(histograms);
    //merge(std::vector<Mat>{histImageBlue, histImageGreen, histImageRed}, histImageCombined);
    imshow("Histogramme", histImage);

    // ... autres codes ...

    //cv::waitKey(0);
    imshow("Histogramme Rouge", histImageRed);
    imshow("Histogramme Vert", histImageGreen);
    imshow("Histogramme Bleu", histImageBlue);
    //imshow("Histogramme Combiné", histImageCombined);
    cv::waitKey(0);

    //////// Test Qt //////////

    QApplication a(argc, argv);
    FenetrePrincipale mainWindow(Bibliotheque);
    mainWindow.show();
    //return 0;
    return a.exec();

}
