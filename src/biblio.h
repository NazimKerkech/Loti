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
    // enregistrer des .bib à partir d'une bibliotheque
    void saveLibraryWithImages();

    // MAJ du fichier CSV
    void updateCSV();
    void ajouter_image(Image img);
    // tri d'images dans la biblio
    Biblio filterImages(string source, int numero, double coutMin, double coutMax);
    void pushImage(Image img);
    void vider_images();
    // save le.bib
    void saveBib();
    double getPrixMax();
    double getPrixMin();
};

#endif // BIBLIO_H

