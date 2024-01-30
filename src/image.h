#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Image {
private:
	string _source; //un seul mot
	string _titre; //plusieurs mots
	int _numero;
	double _cout;
	char _acces; // 'L' ou 'R'
	// XXX � rajouter
	Mat _img;

public:
	Image(vector<string>); //charger l'image � partir de son nom de fichier, et lui donner les descripteurs
	Image();
	void afficheDescripteurs() const;
	Mat getImg();
	void afficheImage() const;

	cv::Vec3b BGR(int, int); // retourne le pixel en (x,y)

	int rows() const; // taille des x 
	int cols() const; // taille des y

	string get_source() const;
	int get_numero() const;
	double get_cout() const;
	string get_titre() const;
	char get_acces() const;

	void set_source(string) ;
	void set_numero(string) ;
	void set_cout(string) ;
	void set_titre(string) ;
	void set_acces(string) ;

	//pour le tri des images
    static void tri_Cout(vector<Image>& bibliotheque); //il demandait static
	/*
		Traitement d'image :
	*/
	
	Mat houghLineTransform(float = 0.7);
	Mat convolution(Mat filtre);
	Mat laplacien(int noFiltre);
	Mat Segmentation(double rSeuil, double gSeuil, double bSeuil);
	Mat rehaussementContour(int noFiltre);
	tuple<Mat, Mat, Mat, Mat> histogramme();
};

vector<vector<string>> loadCSV(string);
void writeCSV(string, vector<vector<string>>);
void appendCSV(string filename, vector<string> ligne);

vector<Image> createBib(vector<vector<string>>);

Mat loadImage(const string&); // charge l'image dans la base de donnee (et a une bibliotheque)
void addImage(string, string); // ajoute l'image � la base de donnee
void delImage(string, string); // supprime l'image d'une bibliotheque
