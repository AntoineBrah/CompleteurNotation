#include <iostream>
#include <cstdlib>
#include "LectureFichier.h"
#include "Initialisation.h"
#include "Point.h"

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
        lectureFichier File(argv[1]);

        separator();

        Point p1(3,5);
        cout << p1 << endl;

        separator();

        cout << convertPointToPosition(p1) << endl;
        
        separator();

        Position p("b7");

        cout << convertPositionToPoint(p) << endl;

        separator();

        Point p2(2,1);
        Point p3(3,1);

        p2 += p3;

        cout << p2 << endl;

    




    }

    return 0;
}