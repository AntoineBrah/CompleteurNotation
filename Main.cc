#include <iostream>
#include <cstdlib>
#include "LectureFichier.h"
#include "Initialisation.h"
#include "TraitementCoups.h"
#include "Point.h"
#include "Pion.h"

#define separator() cout << "---------------------------------" << endl


int main(int argc, char* argv[]){

    if(argc != 2){
        if(argc < 2){
            cout << "ERREUR : Vous devez passer un fichier en argument." << endl;
        }
        if(argc>2){
            cout << "ERREUR : Vous devez passer un unique fichier en argument." << endl;   
        }
        return EXIT_FAILURE;
    }
    else{
        vector<Cellule*> *listeCellules = initialiserCellules();

        for(unsigned int i=0; i<=listeCellules->size()-1; i++){
            separator();
            cout << listeCellules->at(i)->toString() << endl;
            separator();
        }

    }

    return 0;
}