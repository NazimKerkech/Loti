#include "utilisateur.h"
#include <fstream>
#include <iostream>
#include <sstream>

Utilisateur::Utilisateur() : userExist(false) {
}

Utilisateur::~Utilisateur() {
}

std::string Utilisateur::getUserAccess() const {
    return userAccess;
}

bool Utilisateur::login(const std::string& username) {
    userExist = false; // Reset the userExist flag

    for (const auto& row : userData) {
        if (!row.empty() && row[0] == username) {
            userExist = true;
            if (row.size() > 1) {
                userAccess = row[1];
            }
            break;
        }
    }

    return userExist;
}

void Utilisateur::loadCSV(const std::string& filename) {
    std::ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        userData.push_back(row);
    }

    // Close the file stream
    file.close();
}
std::string Utilisateur::getUserAccess() {
    return this->userAccess;
}

const std::vector<std::vector<std::string>>& Utilisateur::getUserData() const {
    return userData;
}

