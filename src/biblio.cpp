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
void Biblio::set_images(int i, Image image)
{
    _bib[i] = image;
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

//save les .bib a partir dune bibliotheque

void Biblio::saveLibraryWithImages() {
    ofstream bibFile(_bibName);
    if (bibFile.is_open()) {
        for (auto& image : _bib) {
            bibFile << "Titre: " << image.get_titre() << endl;
            // Enregistrer l'image
            string imageFileName = "images/" + image.get_titre() + ".jpg";
            cv::imwrite(imageFileName, image.getImg());
            bibFile << "Chemin de l'image: " << imageFileName << endl;
            bibFile << "\n";
        }
        bibFile.close();
    } else {
        cerr << "Erreur : Impossible d'ouvrir le fichier" << endl; //message derreur
    }
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
void Biblio::pushImage(Image img) {
    this->_bib.push_back(img);
}

void Biblio::vider_images() {
    this->_bib.clear();
}
// tri des images en fct de leur numero,cout et source 
Biblio Biblio::filterImages(string source, int numero, double coutMin, double coutMax) {
    Biblio bibliotheque_filtree = Biblio();
    bibliotheque_filtree.vider_images();

    for (const auto& image : _bib) {
        if (source=="" || image.get_source() == source) {
            if (numero==0 || image.get_numero() == numero) {
                if (image.get_cout() >= coutMin && image.get_cout() <= coutMax) {
                    bibliotheque_filtree.pushImage(image);
                }
            }
        }
    }
    return bibliotheque_filtree;
}

//enregistrer un .bib a partir d'une bibliotheque
void Biblio::saveBib() {
    std::ofstream bibFile(_bibName + ".bib");

    if (!bibFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier .bib" << std::endl;
            return;
    }

    // Écrire le contenu du fichier .bib
    for (const auto& image : _bib) {
        bibFile << "Titre: " << image.get_titre() << std::endl;
        bibFile << "Numero: " << image.get_numero() << std::endl;
        bibFile << std::endl;  
    }

    bibFile.close();
}
////////////////
// fonction getprix max
double Biblio::getPrixMax() {
    if (_bib.empty()) {
        std::cerr << "Erreur : La bibliothèque est vide." << std::endl;
            return 0.0;  
    }

    double prixMax = _bib[0].get_cout();

    for (const auto& image : _bib) {
        double prix = image.get_cout();
        if (prix > prixMax) {
            prixMax = prix;
        }
    }

    return prixMax;
}

// fct get prix min
double Biblio::getPrixMin(){
    if (_bib.empty()) {
        std::cerr << "Erreur : La bibliothèque est vide." << std::endl;
            return 0.0;  
    }

    double prixMin = _bib[0].get_cout();

    for (const auto& image : _bib) {
        double prix = image.get_cout();
        if (prix < prixMin) {
            prixMin = prix;
        }
    }

    return prixMin;
}
