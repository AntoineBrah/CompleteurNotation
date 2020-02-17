#include <iostream>
#include <cstdlib>
#include "LectureFichier.h"
#include "Initialisation.h"
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
        Pion p1(Blanc, type::Pion, "e2");

        cout << "Le pion p1 est en position : " << p1.getPosition() << ", sa liste des coups possibles est : "; 
        p1.printListeCoupsPossibles();

    }

    return 0;
}