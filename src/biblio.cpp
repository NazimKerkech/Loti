#include "biblio.h"

#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "image.h"
using namespace std;
using namespace cv;
namespace fs = std::filesystem;

const string LOTI_DIR(SOURCE_DIR);
const string DATA_DIR(LOTI_DIR + "/dta/");


// biblio.cpp

Biblio::Biblio() {
    _bibName = DATA_DIR+"defaut.bib";
    loadLibrary();
}

Biblio::Biblio(std::string bibName) : _bibName(bibName) {
    loadLibrary();
}

vector<Image> Biblio::get_images()
{
    return _bib;
}

void Biblio::displayDescriptors() {
    for (auto& image : _bib) {
        image.afficheDescripteurs();
    }
}

//delete avec le titre
void Biblio::delImage(string titre) {
    // Using iterator to search for the image
    for (auto it = _bib.begin(); it != _bib.end(); ++it) {
        if (it->get_titre() == titre) {
            it = _bib.erase(it);
            updateCSV();
            return;
        }
    }

    //si on trouve pas l'image (l'image n'est pas found)array indexing)
    for (int i = 0; i < _bib.size(); i++) {
        if (_bib[i].get_titre() == titre) {
            _bib.erase(_bib.begin() + i);
            updateCSV();
            return;
        }
    }

   //si on trouve pas l'image
    std::cout << "Erreur : image pas trouvée dans la biblio" << std::endl;
}


//delete num img
void Biblio::delImage2(int numero) {
     vector<vector<string>> bib = loadCSV(_bibName);
    for (auto it = _bib.begin(); it != _bib.end(); ++it) {
        if (it->get_numero() == numero) {
            it = _bib.erase(it);
            break;
        }

    }
    for (int i = 0;i < bib.size(); i++)
    {
        if (bib[i][0] == to_string(numero))
        {
            bib.erase(bib.begin() + i);
            writeCSV(_bibName, bib);
            return;
        }
    }
    std::cout << "Erreur image pas dans la biblio" << std::endl;
    return;
}

void Biblio::loadLibrary() {
    std::vector<std::vector<std::string>> bib = loadCSV(_bibName);
    std::vector<std::vector<std::string>> descriptors = loadCSV(DATA_DIR+"descripteurs.csv");
    std::vector<std::vector<std::string>> descriptorsBib;
    for(int i = 0; i<bib.size(); i++)
    {
        for(int j = 0; j<descriptors.size(); j++)
        {
            if (bib[i][0] == descriptors[j][2])
            {
                descriptorsBib.push_back(descriptors[j]);
            }
        }
    }

    _bib = createBib(descriptorsBib);

}

void Biblio::saveLibrary() {
    std::vector<std::vector<std::string>> descriptors;

    for (auto& image : _bib) {
        std::vector<std::string> imageDescriptors;
        //imageDescriptors.push_back(image.get_titre());
        //imageDescriptors.push_back(image.get_titre());
        //imageDescriptors.push_back(std::to_string(image.rows()));
        //imageDescriptors.push_back(std::to_string(image.cols()));
        //imageDescriptors.push_back(std::to_string(image.getImg().type()));

        imageDescriptors.push_back(std::to_string(image.get_numero()));
        descriptors.push_back(imageDescriptors);
    }

    writeCSV(_bibName, descriptors);
}

void Biblio::updateCSV() {
    saveLibrary();
}
void Biblio::ajouter_image(Image img) {
    vector<string> descripteurs;
    descripteurs.push_back(img.get_source()); // source
    descripteurs.push_back(img.get_titre()); // titre
    descripteurs.push_back(to_string(img.get_numero())); // numero par defaut
    descripteurs.push_back(to_string(img.get_cout())); // cout
    descripteurs.push_back(to_string(img.get_acces())); // acces
    appendCSV(DATA_DIR + "descripteurs.csv", descripteurs);


    this->_bib.push_back(img);
}


