#include <iostream>
#include <cstdlib>
#include <sstream>
#include "LectureFichier.h"
#include "Initialisation.h"
#include "TraitementCoups.h"
#include "EcritureFichier.h"
#include "Point.h"
#include "Pion.h"

extern string plateforme;


int main(int argc, char* argv[]){

    viderFichier("Interface/cellulesBis.json");
    viderFichier("Interface/cellules.json");

    bool estTraite = false;

    if(argc != 3 && argc != 4){
        cout << "\nUsage: chess <plateforme> <fichier> [options...]\n\nParamètres requis :\n\nfichier : contient la partie d'échecs au format PGN\nplateforme : -l (linux), -w (windows) -m (macos)\n\nParamètres optionnels :\n\ntraduction : -t converti un fichier PGN anglo-saxon en fichier PGN français (nécessite d'avoir NodeJS d'installé)\n" << endl;
        return EXIT_FAILURE;
    }
    else{

        if(string(argv[1]) != "-l" && string(argv[1]) != "-m" && string(argv[1]) != "-w"){
            cout << "\nUsage: chess <plateforme> <fichier> [options...]\n\nParamètres requis :\n\nfichier : contient la partie d'échecs au format PGN\nplateforme : -l (linux), -w (windows) -m (macos)\n\nParamètres optionnels :\n\ntraduction : -t converti un fichier PGN anglo-saxon en fichier PGN français (nécessite d'avoir NodeJS d'installé)\n" << endl;
            return EXIT_FAILURE;
        }
        else{
            if(argc == 4){
                if(string(argv[3]) != "-t"){
                    cout << "\nUsage: chess <plateforme> <fichier> [options...]\n\nParamètres requis :\n\nfichier : contient la partie d'échecs au format PGN\nplateforme : -l (linux), -w (windows) -m (macos)\n\nParamètres optionnels :\n\ntraduction : -t converti un fichier PGN anglo-saxon en fichier PGN français (nécessite d'avoir NodeJS d'installé)\n" << endl;
                    return EXIT_FAILURE;
                }
            }
        }

        if(argc == 4)
            system((string("nodejs pgnTranslator.js ") + argv[2]).c_str()); // Traduction du fichier PGN

        plateforme = argv[1]; // Permet de savoir dans quel dossier modifier le fichier Cellules.json
        
        estTraite = traitementCoups(argv[2]);
    }

    
    if(estTraite){

        if(string(argv[1]) == "-l")
            system("./Interface/ChessCompletor-linux-x64/ChessCompletor");
        else if(string(argv[1]) == "-m")
            system("./Interface/ChessCompletor-darwin-x64/ChessCompletor-MacOS.app/Contents/MacOS/ChessCompletor");
        else if(string(argv[1]) == "-w")
            system("./Interface/ChessCompletor-win-x64/ChessCompletor.exe");
    }

    

    return 0; 
}