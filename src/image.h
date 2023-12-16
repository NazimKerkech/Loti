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
	Image(string, vector<string>); //charger l'image � partir de son nom de fichier, et lui donner les descripteurs

	void afficheDescripteurs();
};

vector<vector<string>> loadCSV(string);
void writeCSV(string, vector<vector<string>>);
vector<Image> createBib(vector<vector<string>>);
Mat loadImage(const string&);
