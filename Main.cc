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
        
        /*
        lectureFichier File(argv[1]); // On ouvre le fichier txt en lecture

        if(File.getEstCorrectementOuvert()){ // Si le fichier est correctement ouvert alors, on le traite
            traitementCoups(&File);
            //system("cd Interface ; electron .");
        }
        */


        Piece *p3 = new Fou(Blanc, type::Fou, "h8");
        Piece *p2 = new Pion(Noir, type::Pion, "f3");
        Piece *p4 = new Tour(Noir, type::Tour, "c8");
        Piece *p5 = new Cavalier(Noir, type::Tour, "f6");
        Piece *p1 = new Roi(Blanc, type::Roi, "d3");

        p1->printListeCoupsPossibles();

        delete p3;
        delete p2;
        delete p1;
        delete p4;
        delete p5;

    }

    return 0;
}
