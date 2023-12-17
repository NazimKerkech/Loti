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

using namespace std;
using namespace cv;

const string LOTI_DIR(SOURCE_DIR);
const string DATA_DIR(LOTI_DIR + "/dta/");

#define PI 3.14

Image::Image(vector<string> listDescripteurs)
{
    _img = loadImage(DATA_DIR + listDescripteurs[2]); //ouverture avec le numero de l'image
    
    _source = listDescripteurs[0];
    _titre  = listDescripteurs[1];
    _numero = stoi(listDescripteurs[2]); //convertir str en int
    _cout   = stod(listDescripteurs[3]);
    _acces  = listDescripteurs[4][0]; // normalement un seul charactere
}

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

void Image::afficheDescripteurs()
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
    // Draw the lines
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

    // Display the results
    imshow("Detected Lines", resultImage);
    return resultImage;
}