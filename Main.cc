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

        
        Cellule *p3 = new Cellule(new Fou(Blanc, type::Fou, "h8"));
        Cellule *p4 = new Cellule(new Cavalier(Blanc, type::Cavalier, "b2"));
        Cellule *p5 = new Cellule(new Pion(Noir, type::Pion, "d5"));
        Cellule *p2 = new Cellule(new Roi(Blanc, type::Roi, "e1"));
        

        
        Piece *p1 = new Dame(Blanc, type::Dame, "d3");
        Cellule *c1 = new Cellule(p1);
        /*
        cout << c1->getJSON() << endl;
        */

        /*
        delete p3;
        delete p2;
        delete p4;
        delete p5;
        delete p1;
        */

       
    }

    correctionSyntaxe();

    return 0;
}
