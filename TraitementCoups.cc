#include "TraitementCoups.h"

void traitementCoups(lectureFichier* f){

    lectureFichier *File = f;

    do{
        File->printLigne();
    }while(File->lireLigneSuivante());

    /*
    vector<Cellule*> *listeCellulesInitiales = initialiserCellules();
    vector<Cellule*> *listeCellulesNouvelles = new vector<Cellule*>;
    */



}
