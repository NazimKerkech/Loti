#include "image.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <filesystem>

using namespace std;
using namespace cv;

const string LOTI_DIR(SOURCE_DIR);
const string DATA_DIR(LOTI_DIR + "/dta/");

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