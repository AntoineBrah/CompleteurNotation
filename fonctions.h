#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int lectureFichier(string path, int line){

    string const thisPath(path);
    ifstream fichier(thisPath);
    if(fichier){
        string lignePreced;
        for(int i = 1;i < line;i++){
            getline(fichier,lignePreced);
        }
        string coupBlanc, coupNoir;
        fichier >> coupBlanc;
        fichier >> coupNoir;
        cout << coupBlanc << endl;
        cout << coupNoir << endl; 
    }
    else{
        cout << "erreur lors de l'ouverture du fichier" << endl;
    }
    return 0;

}