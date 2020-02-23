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
        
        lectureFichier File(argv[1]); // On ouvre le fichier txt en lecture

        
        if(File.getEstCorrectementOuvert()){ // Si le fichier est correctement ouvert alors, on le traite

            traitementCoups(&File);
        }
        


        /*
        Piece *p1 = new Cavalier(Blanc, type::Cavalier, "g1");

        Cellule *c1 = new Cellule(p1);
        
        p1->setPostion("g3");
        updateListeCoupsPossiblesAll();

        Cellule *c2 = new Cellule(p1);

        c1->setCSP(c2); 

        p1->setPostion("g5");
        updateListeCoupsPossiblesAll();


        Cellule *c3 = new Cellule(p1);

        c2->setCSP(c3);
    
        cout << "Adresse c1 : " << c1 << "\nAdresse c2 : " << c2 << "\nAdresse c3 : " << c3 << "\nAdresse de CSP : " << getDernierCSP(c1) << endl;

        //Cellule *c = getDernierCSP(c1);

        //cout << "c pointe vers : " << c << endl;
        */
        
        /*
        vector<Cellule*> *initialisationEchiquier = initialiserCellules();

        for(Cellule* cell : (*initialisationEchiquier)){
            delete cell;
        }

        initialisationEchiquier->clear();
        */

       
    }

    correctionSyntaxe();
    //system("cd Interface ; electron .");

    return 0;
}
