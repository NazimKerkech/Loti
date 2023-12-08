#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Image {
private:
	string source; //un seul mot
	string titre; //plusieurs mots
	int numero;
	double cout;
	char acces; // 'L' ou 'R'
	// XXX à rajouter
	// Mat img
public:
	Image(string); //charger l'image à partir de son nom de fichier


};

vector<vector<string>> loadDescriteurs(string);
