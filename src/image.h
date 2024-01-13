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

	void afficheDescripteurs();
	Mat getImg();
	void afficheImage() const;

	cv::Vec3b BGR(int, int); // retourne le pixel en (x,y)

	int rows() const; // taille des x 
	int cols() const; // taille des y

	string get_titre() const;
	/*
		Traitement d'image :
	*/
	
	Mat houghLineTransform(float = 0.7);
	Mat convolution(Mat filtre);


};

vector<vector<string>> loadCSV(string);
void writeCSV(string, vector<vector<string>>);
void appendCSV(vector<vector<string>>);

vector<Image> createBib(vector<vector<string>>);

Mat loadImage(const string&); // charge l'image dans la base de donnee (et a une bibliotheque)
void addImage(string, string); // ajoute l'image � la base de donnee
void delImage(string, string); // supprime l'image d'une bibliotheque
