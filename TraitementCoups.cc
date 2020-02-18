#include "TraitementCoups.h"

void traitementCoups(lectureFichier* f){

    lectureFichier *File = f;

    while(File->lireLigneSuivante()){
        File->printLigne();
    }

    /*
    vector<Cellule*> *listeCellulesInitiales = initialiserCellules();
    vector<Cellule*> *listeCellulesNouvelles = new vector<Cellule*>;
    */



}
