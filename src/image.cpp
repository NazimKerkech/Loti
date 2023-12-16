#pragma once
#include "image.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

Image::Image(string ImgFileName, vector<string> listDescripteurs)
{
    // image : Mat = imread(ImgFileName)
    
    _source = listDescripteurs[0];
    _titre = listDescripteurs[1];
    _numero = stoi(listDescripteurs[2]); //convertir str en int
    _cout = stod(listDescripteurs[3]);
    _acces = listDescripteurs[4][0]; // normalement un seul charactere
}

vector<vector<string>> loadCSV(string filename = "descripteurs.csv")
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

vector<Image> createBib(vector<vector<string>> data)
{
    int nbImg = data.size();
    vector<Image> bibliotheque;
    for (int i = 0; i < nbImg; i++)
    {
        /*
            recuperer le nom de l'image avant 
        */
        bibliotheque.push_back(Image("image.png", data[i]));
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
