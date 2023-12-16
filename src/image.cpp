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
    if (remove(filename.c_str())) { cout << "Error deleting file."; };
    if (rename(tempFilename.c_str(), filename.c_str())) { cout << "Error renaming temp."; }
}

vector<Image> createBib(vector<vector<string>> tableauDescripteurs)
{
    int nbImg = tableauDescripteurs.size();
    vector<Image> bibliotheque;
    for (int i = 0; i < nbImg; i++)
    {
        /*
            recuperer le nom de l image avant 
        */
        bibliotheque.push_back(Image("image.png", tableauDescripteurs[i]));
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
