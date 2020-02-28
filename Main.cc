#include <iostream>
#include <cstdlib>
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
    }

    correctionSyntaxe();

    
    if(estTraite){
        system("cd Interface ; electron .");
    }

    return 0;
}
