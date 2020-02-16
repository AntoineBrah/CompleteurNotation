#include <iostream>
#include <cstdlib>
#include "LectureFichier.h"
#include "Initialisation.h"

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

        while(File.lireLigneSuivante()){
            File.getLigne();
        }













    }

    return 0;
}