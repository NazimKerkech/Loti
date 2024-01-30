#ifndef BIBLIO_H
#define BIBLIO_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "image.h"


using namespace std;

class Biblio {
private:
    std::vector<Image> _bib;
    std::string _bibName;

public:
    Biblio();
    Biblio(std::string);

    vector<Image> get_images();
    void set_images(int, Image);
    // afficher les descript
    void displayDescriptors();

    // effacer l'image
    void delImage(std::string); //titre
    void delImage2(int);        //num de l'image

    // charger les images du csv
    void loadLibrary();

    // enregistrer la biblio au csv
    void saveLibrary();

    // MAJ du fichier CSV
    void updateCSV();
    void ajouter_image(Image img);
    // tri d'images dans la biblio
    vector<Image> filterImages(const string& sourceMin, const string& sourceMax,
                               int numeroMin, int numeroMax,
                               double coutMin, double coutMax);

    // save le.bib
    void saveBib();
};

#endif // BIBLIO_H

