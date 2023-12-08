#pragma once
#include "image.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<string>> loadDescriteurs(string filename = "descripteurs.csv")
{
    ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << endl;
    }

    vector<std::vector<std::string>> data; // 2D vector to store CSV data

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

    // Displaying the CSV data (for demonstration purposes)
    for (const auto& row : data) 
    {
        for (const auto& cell : row) 
        {
            std::cout << cell << "\t";
        }
        std::cout << endl;
    }

    // Close the file stream
    file.close();
    return data;
}