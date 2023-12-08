#include <iostream>
#include <vector>
#include "image.h"

using namespace std;

const string LOTI_DIR(SOURCE_DIR);

int main() {
    
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hello there ;)" << std::endl;
    cout << "Ol Korect !" <<endl;

    cout << "Ahmed !" <<endl;

    cout << "heeeeyy" << endl;
    cout << "heeeeyy" << endl;

    vector<vector<string>> data;
    data = loadDescriteurs(LOTI_DIR+"/dta/descripteurs.csv");

    cout << LOTI_DIR + "/dta/descripteurs.csv";
    return 0;
}
