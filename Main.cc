#include <iostream>
#include <cstdlib>
#include <sstream>
#include "LectureFichier.h"
#include "Initialisation.h"
#include "TraitementCoups.h"
#include "EcritureFichier.h"
#include "Point.h"
#include "Pion.h"


#define separator() cout << "---------------------------------" << endl


int main(int argc, char* argv[]){

    viderFichier();

    bool estTraite = false;

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
        
        lectureFichier File(argv[1]); // On ouvre le fichier txt en lecture
        
        if(File.getEstCorrectementOuvert()){ // Si le fichier est correctement ouvert alors, on le traite
            traitementCoups(&File);
            estTraite = true;
        }

        /*
        Piece *Tb1 = new Tour(Blanc, type::Tour, "a1"); // Tour blanche n°1 situé en a1
        Cellule* cTb1 = new Cellule(Tb1);
        Tb1->setFirstCell(cTb1);


        // On déplace la tour
        Tb1->setPostion("a5");
        Cellule* cTb1_2 = new Cellule(Tb1);

        cTb1->setCSP(cTb1_2);

        cout << Tb1->getFirstCell()->toString() << endl;
        */


        //cout << "cTb1 : " << cTb1 << "\nTb1->setFirstCell() : " << Tb1->getFirstCell() << endl;
        
    }

    correctionSyntaxe();

    if(estTraite){
        system("cd Interface ; electron .");
    }

    return 0;
}
