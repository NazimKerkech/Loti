#include "image.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <filesystem>
#include <cmath>
#include <ctime>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

const string LOTI_DIR(SOURCE_DIR);
const string DATA_DIR(LOTI_DIR + "/dta/");

#define PI 3.14

Image::Image(vector<string> listDescripteurs)
{
    std::hash<std::string> hasher;  // Hash function for strings

    _img = loadImage(DATA_DIR + listDescripteurs[2]); //ouverture avec le numero de l'image

    _source = listDescripteurs[0];
    _titre  = listDescripteurs[1];
    _numero = hasher(listDescripteurs[2]); //convertir str en int
    _cout   = stod(listDescripteurs[3]);
    _acces  = listDescripteurs[4][0]; // normalement un seul charactere
}
Image::Image() {}


vector<vector<string>> loadCSV(string filename)
{
    ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << endl;
    }

    vector<vector<string>> data; // 2D vector to store CSV data

    string line;
    while (getline(file, line)) 
    {
        vector<std::string> row;
        stringstream lineStream(line);
        string cell;

        while (getline(lineStream, cell, ',')) // Assuming ',' as the delimiter
        { 
            row.push_back(cell);
        }
        data.push_back(row);
    }
    // Close the file stream
    file.close();
    data.erase(data.begin()); //enlever entete
    return data;
}

void writeCSV(string filename, vector<vector<string>> data)
{
    string tempFilename("temp_write.csv");
    ifstream inFile(filename); // Nom du fichier CSV en entrée
    ofstream outFile(tempFilename); // Nom du fichier CSV en sortie (temporaire)
    string line;

    if (!inFile.is_open()) {
        cout << "Impossible d'ouvrir le fichier d'entrée." << endl;
        return;
    }

    if (!outFile.is_open()) {
        cout << "Impossible de créer le fichier temporaire." << endl;
        return;
    }

    // Copy the first line of input.csv to output.csv
    getline(inFile, line);
    outFile << line << endl;

    // Copy the lines of data to output.csv
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            outFile << data[i][j] << ',';
        }
        outFile << endl;
    }

    inFile.close();
    outFile.close();

    // Replace the original file with the new file
    if (remove(filename.c_str())) { cout << "Error deleting file.\n"; };
    if (rename(tempFilename.c_str(), filename.c_str())) { cout << "Error renaming temp.\n"; }
}

void appendCSV(string filename, vector<string> ligne)
{
    ofstream file(filename, std::ios::app);

    if (file.is_open()) {
        // Nouvelle ligne à ajouter à la fin du fichier CSV
        for (int i = 0; i < ligne.size(); i++)
        {
            file << ligne[i] << ",";
        }
        file << endl;

        std::cout << "Nouvelle ligne ajoutée avec succès." << std::endl;
        file.close();
    }
    else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }
}

vector<Image> createBib(vector<vector<string>> tableauDescripteurs)
{
    int nbImg = tableauDescripteurs.size();
    vector<Image> bibliotheque;
    for (int i = 0; i < nbImg; i++)
    {
        bibliotheque.push_back(Image(tableauDescripteurs[i]));
    }
    return bibliotheque;
}

void Image::afficheDescripteurs() const
{
    cout << "Source : " << _source << endl;
    cout << "Titre :  " << _titre << endl;
    cout << "Numero : " << _numero << endl;
    cout << "Cout :   " << _cout << endl;
    cout << "Acces :  " << _acces << endl;
    // xxx
    cout << endl;
}

Mat loadImage(const string& imageName) //permet de charger une image avec seulement sont numero
{
    vector<string> extensions = { ".png", ".jpg", ".bmp", ".tif", ".tiff", ".jpeg"}; // extensions possibles
    Mat image;

    for (const auto& ext : extensions) {
        string fullPath = imageName + ext;
        
        if (filesystem::exists(fullPath))
        {
            image = imread(fullPath);
            break;
        }
    }
    if (image.empty()) {
        cout << "Erreur chargement de l'image " << imageName << endl;
    }
    return image;
}


void addImage(string filePath, string bibName)
{
    // Chemin vers l'image source
    fs::path imagePath = filePath;

    // Chemin vers le répertoire de destination
    time_t now = time(0); // unique id
    string numeroImage = to_string(now);
    fs::path destinationPath = DATA_DIR + numeroImage;

    // Vérifier si le fichier source existe
    if (fs::exists(imagePath)) {
            // Obtenir le nom de fichier de l'image source
            // std::string fileName = imagePath.filename().string();
            fs::path extension = imagePath.extension();// .string();
            destinationPath += extension;
            try {
                // Copier le fichier vers le répertoire de destination
                fs::copy_file(imagePath, destinationPath, fs::copy_options::overwrite_existing);
                std::cout << "L'image a été copiée avec succès vers " << destinationPath << std::endl;
            }
            catch (std::exception const& ex) {
                std::cout << "Une erreur s'est produite : " << ex.what() << std::endl;
                return;
            }
    }
    else {
        std::cout << "Le fichier source n'existe pas." << std::endl;
        return;
    }

    vector<string> descripteurs;
    descripteurs.push_back("SourceDefaut"); // source
    descripteurs.push_back("Titre par Defaut"); // titre
    descripteurs.push_back(numeroImage); // numero par defaut
    descripteurs.push_back("0.0"); // cout
    descripteurs.push_back("L"); // acces
    cout << "ok "<< numeroImage<< " " << descripteurs.size() <<"\n";
    Image imageAjoute(descripteurs);

    appendCSV(DATA_DIR + "descripteurs.csv", descripteurs);
    appendCSV(DATA_DIR + bibName, {numeroImage});

    /*
    Ajouter l'ajou de l'image à la bibliotheque
    Ajouter l'ajou manuel des descripteurs
    */
    return;
}

void delImage(string numeroImg, string bibName)
{
    vector<vector<string>> bib = loadCSV(DATA_DIR + bibName);
    for (int i = 0;i < bib.size(); i++)
    {
        if (bib[i][0] == numeroImg)
        {
            bib.erase(bib.begin() + i);
            writeCSV(DATA_DIR + bibName, bib);
            return;
        }
    }
    cout << "Erreur l'image n'est pas dans la bibliotheque" << endl;
}

Mat Image::getImg() 
{
    return _img;
}

void Image::afficheImage() const
{
    imshow(this->_titre, this->_img);
}

cv::Vec3b Image::BGR(int x, int y)
{
    return this->_img.at<cv::Vec3b>(x, y);
}

int Image::rows() const
{
    return _img.rows;
}

int Image::cols() const
{
    return _img.cols;
}
string Image::get_source() const
{
    return _source;
}
string Image::get_titre() const
{
    return _titre;
}
int Image::get_numero() const
{
    return _numero;
}
double Image::get_cout() const
{
    return _cout;
}
char Image::get_acces() const
{
    return _acces;
}
void Image::tri_Cout(vector<Image>& bibliotheque) { // Tri d'images par ordre décroissant
    sort(bibliotheque.begin(), bibliotheque.end(), [](const Image& img1, const Image& img2) {
        return img1._cout > img2._cout;
    });
}

// Traitement d'image
Mat Image::houghLineTransform(float pourcentage)
{
    Mat contours, greyMat, resultImage = this->_img.clone();
    cvtColor(resultImage, greyMat, cv::COLOR_BGR2GRAY);
    Canny(greyMat, contours, 50, 205, 3);
    
    float seuille(0.0), angle(0.0), pasAngle(0.5);
    int rayon(0), total(0), max(0);
    int cols(180 / pasAngle);
    int rows(sqrt(contours.rows * contours.rows + contours.cols * contours.cols));

    vector<vector<int>> M(rows, vector<int>(cols, 0));

    for (int i = 0; i < contours.rows; i++)
    {
        for (int j = 0; j < contours.cols; j++)
        {
            if (contours.at<uchar>(i, j) != 0)
            {
                for (angle =0; angle < 180; angle += pasAngle)
                {
                    int numero_angle(angle/pasAngle);
                    rayon = (int) round(j * cos(angle/180* PI) + i * sin(angle/180* PI));

                    if (rayon >= 0) {
                        M[rayon][numero_angle] += 1;
                        if (M[rayon][numero_angle] > max)
                        {
                            max = M[rayon][numero_angle];
                        }
                    }  
                }
            }
        }
    }
    seuille = pourcentage * max;
    vector<float> listRayons, listAngles;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (M[i][j] > seuille) 
            {
                listRayons.push_back(i);
                listAngles.push_back(j*pasAngle/180*PI);
            }
        }
    }
    // Dessin des lignes
    for (size_t i = 0; i < listRayons.size(); i++)
    {
        float rho = listRayons[i], theta = listAngles[i];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = (int)round(x0 + 10000 * (-b));
        pt1.y = (int)round(y0 + 10000 * (a));
        pt2.x = (int)round(x0 - 10000 * (-b));
        pt2.y = (int)round(y0 - 10000 * (a));
        line(resultImage, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
    }

    // Affichage
    //imshow("Detected Lines", resultImage);
    return resultImage;
}

Mat Image::convolution(Mat filtre) {
    //Mat image = this->getImg();
    Mat convoluee = Mat::zeros(_img.size(), CV_32FC3);

    int bord_i = filtre.rows/2;
    int bord_j = filtre.cols/2;
    for(int i=bord_i; i< convoluee.rows-bord_i; i++) {
        for(int j=bord_j; j< convoluee.cols-bord_j; j++) {
            for(int k=0; k<filtre.rows; k++) {
                for(int l=0; l<filtre.cols; l++) {
                    convoluee.at<Vec3f>(i, j)[0] += _img.at<Vec3b>(i + k - bord_i, j + l - bord_j)[0] * filtre.at<float>(k, l);
                    convoluee.at<Vec3f>(i, j)[1] += _img.at<Vec3b>(i + k - bord_i, j + l - bord_j)[1] * filtre.at<float>(k, l);
                    convoluee.at<Vec3f>(i, j)[2] += _img.at<Vec3b>(i + k - bord_i, j + l - bord_j)[2] * filtre.at<float>(k, l);
                }
            }
        }
    }
    convoluee.convertTo(convoluee, CV_8UC3); // or CV_32F works (too)
    return convoluee.clone();
}

//Laplacien
Mat Image::laplacien(int noFiltre) {
    // Dle kernel du laplacien
    Mat kernel;
    switch (noFiltre){
    case 1:
     kernel = (Mat_<float>(3, 3) <<
                      0,  1, 0,
                  1, -4, 1,
                  0,  1, 0);
        break;


    case 3:
     kernel = (Mat_<float>(7, 7)<< 0,    0.0037,    0.0147,    0.0256,    0.0147,    0.0037, 0,
                 0.0037 ,   0.0147,    0.0293 ,   0.0220 ,   0.0293,    0.0147,    0.0037,
                 0.0147,    0.0293,   -0.0147,   -0.0879 ,  -0.0147,    0.0293  ,  0.0147,
                 0.0256,    0.0220,   -0.0879 ,  -0.2198  , -0.0879,    0.0220 ,   0.0256,
                 0.0147,    0.0293,   -0.0147,   -0.0879 ,  -0.0147,    0.0293,    0.0147,
                 0.0037,    0.0147,    0.0293 ,   0.0220,    0.0293,    0.0147,    0.0037,
                   0 ,   0.0037,    0.0147,    0.0256,    0.0147,    0.0037,         0);

    break;
    default:
     kernel =  (Mat_<float>(5, 5)<<   0  ,  0.0625,    0.1250 ,   0.0625,         0,
                   0.0625    ,     0 ,  -0.1250 ,        0 ,   0.0625,
                   0.1250 ,  -0.1250 ,  -0.5000,   -0.1250  ,  0.1250,
                   0.0625  ,       0,   -0.1250 ,        0   , 0.0625,
                   0   , 0.0625   , 0.1250,    0.0625,         0);
}
    Mat laplacien_res;
    cv::filter2D(_img, laplacien_res, -1, kernel);

    return laplacien_res;
}

//Segmentation
Mat Image::Segmentation(double rSeuil, double gSeuil, double bSeuil) {
    Mat resultat = Mat::zeros(this->_img.size(), CV_8UC3);
    for (int i = 0; i < this->rows(); ++i) {
        for (int j = 0; j < this->cols(); ++j) {
            Vec3b pixel = this->_img.at<Vec3b>(i, j); // référence pixel
            if (pixel[0] > bSeuil && pixel[1] > gSeuil && pixel[2] > rSeuil) {
                resultat.at<Vec3b>(i, j) = {255, 255, 255};
            }
        }
    }
    return resultat.clone();
}
//Rehaussement
Mat Image::rehaussementContour(int noFiltre){
    Mat imageComposante[3];
    Mat contourComposante[3];
    int i;
    int nbComposante = _img.channels() ;
    vector<Mat> imageRehaussementComposante;

    Mat contourImage= laplacien(noFiltre);
    Mat rehaussement;
    // Addition de l'image originale et de l'image des contours (rehaussement)
    if(nbComposante == 1){
        rehaussement = _img + contourImage;
    }else {
        split(_img, imageComposante) ;
        split(contourImage, contourComposante);
        for (i = 0; i <3 ; i++) {
            imageRehaussementComposante.push_back(imageComposante[i] - contourComposante[i]);
        }
        merge(imageRehaussementComposante, rehaussement);
    }
    // Normalisation pour éviter des valeurs en dehors de la plage 0-255
    normalize(rehaussement, rehaussement, 0, 255, NORM_MINMAX);
    // Affichage de l'image rehaussée des contours
    // imshow("Image avec rehaussement de contour", rehaussement);


    return rehaussement;
}

// Histogramme
tuple<Mat, Mat, Mat, Mat> Image::histogramme() {
    Mat image = this->getImg();
    Mat histImage = Mat::zeros(256, 256, CV_8UC3);  // Image pour afficher l'histogramme en NVG
    Mat imageGray;
    // niveaux de gris
    cvtColor(image, imageGray, COLOR_BGR2GRAY);  // Convertir en niveaux de gris

    vector<int> hist(256, 0);
    for (int i = 0; i < imageGray.rows; i++) {
        for (int j = 0; j < imageGray.cols; j++) {
            int intensity = imageGray.at<uchar>(i, j);
            hist[intensity]++;
       }
    }

    int maxCount = *max_element(hist.begin(), hist.end());
    for (int i = 0; i < 256; i++) {
        int barHeight = static_cast<int>(hist[i] * 256.0 / maxCount);
        //line(histImage, Point(i, 256), Point(i, 256 - barHeight), Scalar(255, 255, 255));
        // Choisissez la couleur en fonction du canal
        Scalar color;
        color = Scalar(255, 255, 255);

        // Dessinez la ligne dans l'histogramme approprié
        line(histImage, Point(i, 256), Point(i, 256 - barHeight), color);
    }

    // Images pour afficher les histogrammes de chaque canal
    Mat histImageRed = Mat::zeros(256, 256, CV_8UC3);
    Mat histImageGreen = Mat::zeros(256, 256, CV_8UC3);
    Mat histImageBlue = Mat::zeros(256, 256, CV_8UC3);

    //Mat histImageCombined;
    
    // Calculez et affichez l'histogramme pour chaque canal
    for (int channel = 0; channel < image.channels(); ++channel) {
        vector<int> hist(256, 0);

        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                int intensity = image.at<Vec3b>(i, j)[channel];
                hist[intensity]++;
            }
        }

        // Normalizez l'histogramme pour l'affichage
        int maxCount = *max_element(hist.begin(), hist.end());
        for (int i = 0; i < 256; i++) {
            int barHeight = static_cast<int>(hist[i] * 256.0 / maxCount);
            //line(histImage, Point(i, 256), Point(i, 256 - barHeight), Scalar(255, 255, 255));
            // Choisissez la couleur en fonction du canal
            Scalar color;
            if (channel == 0)      // canal bleu
                color = Scalar(255, 0, 0);
            else if (channel == 1) // canal vert
                color = Scalar(0, 255, 0);
            else                   // canal rouge
                color = Scalar(0, 0, 255);

            // Dessinez la ligne dans l'histogramme approprié
            if (channel == 0)
                line(histImageBlue, Point(i, 256), Point(i, 256 - barHeight), color);
            else if (channel == 1)
                line(histImageGreen, Point(i, 256), Point(i, 256 - barHeight), color);
            else
                line(histImageRed, Point(i, 256), Point(i, 256 - barHeight), color);
        }
    }

    //vector<Mat> channels;
    //channels.push_back(histImageRed);
    //channels.push_back(histImageGreen);
    //channels.push_back(histImageBlue);

    //Mat histImageCombined;
    //cv::merge(channels, histImageCombined);

    return make_tuple(histImageBlue, histImageGreen, histImageRed, histImage);
}
