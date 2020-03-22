#include "LectureFichier.h"

lectureFichier::lectureFichier(string fichier) : ligne(""), cb(""), cn(""), estCorrectementOuvert(false){

    monFlux.open(fichier.c_str()); // obligé de rajouter '.c_str()' car le constructeur de ifstream prend un 'const char*' et non pas un 'string' en paramètre.

    if(monFlux){
        cout << "[i] " << fichier << " : ouverture en lecture réussie.\n" << endl;
        estCorrectementOuvert = true;
        getline(monFlux, ligne);
        traiterLigne();
    }
    else{
        cout << fichier << " : ouverture en lecture échouée." << endl;
    }
}

void lectureFichier::printLigne() const{
    cout << ligne << endl;
}

int lectureFichier::lireLigneSuivante(){
    if(getline(monFlux, ligne)){
        traiterLigne();
        return 1;
    }
    else{
        return 0;
    }
}

bool lectureFichier::getEstCorrectementOuvert() const{
    return estCorrectementOuvert;
}

string lectureFichier::getCoupBlanc() const{
    return cb;
}

string lectureFichier::getCoupNoir() const{
    return cn;
}

void lectureFichier::traiterLigne(){
    string s;
    s = ligne;
    int pos = s.find_first_of(" ");
    
    cb = s.substr(0,pos);

    // Cas ou il n'y a pas d'espace et donc on finit avec un coup blanc
    if(pos == -1){
        cn = "";
    }
    else{
        cn = s.substr(pos+1); // si on précise pas le deuxième paramètre, ça va jusqu'à la fin de la chaine
    }
}

lectureFichier::~lectureFichier(){
    monFlux.close();
}


void detecterCoup(string coup, vector<string> &description){

    regex pion("[a-h]?x?[a-h]{1}[1-8]{1}(=[DFCT])?[+#]?"); // regex pour un pion
    regex piece("[RDFCT]{1}[a-h1-8]?x?[a-h]{1}[1-8]{1}[+#]?"); // regex pour une piece
    regex roque("O-O(-O)?"); // regex pour le roque

    if(regex_match(coup, pion)){
        
        regex deplacementPion("[a-h]{1}[1-8]{1}(=[DFCT])?[+#]?");
        regex mangePion("[a-h]{1}x{1}[a-h]{1}[1-8]{1}(=[DFCT])?[+#]?");

        if(regex_match(coup, deplacementPion)){ // Si le pion ne fait que se déplacer (colonne vide)

            regex promotionPion("[a-h]{1}[1-8]{1}(=[DFCT]){1}[+#]?");

            if(regex_match(coup, promotionPion)){ // S'il y a promotion...

                regex echecOuMatPion("[a-h]{1}[1-8]{1}(=[DFCT]){1}[+#]{1}");

                if(regex_match(coup, echecOuMatPion)){ // S'il y a échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(0,2)); // Déplacement
                    description.push_back(coup.substr(2,2)); // Promotion
                    description.push_back(coup.substr(4,1)); // echec

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(0,2)); // Déplacement
                    description.push_back(coup.substr(2,2)); // Promotion
                    description.push_back(""); // echec
                }

            }
            else{ // S'il n'y a pas promotion...

                regex echecOuMatPion("[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, echecOuMatPion)){ // S'il y a échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(0,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(2,1)); // echec

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(0,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    
                }

            }
        }
        else if(regex_match(coup, mangePion)){ // Si le pion mange une pièce (colonne non vide)

            regex promotionPion("[a-h]{1}x{1}[a-h]{1}[1-8]{1}(=[DFCT]){1}[+#]?");

            if(regex_match(coup, promotionPion)){ // S'il y a promotion...

                regex echecOuMatPion("[a-h]{1}x{1}[a-h]{1}[1-8]{1}(=[DFCT]){1}[+#]{1}");

                if(regex_match(coup, echecOuMatPion)){ // S'il y a échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(coup.substr(0,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(coup.substr(4,2)); // Promotion
                    description.push_back(coup.substr(6,1)); // echec

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(coup.substr(0,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(coup.substr(4,2)); // Promotion
                    description.push_back(""); // echec
                }

            }
            else{ // S'il n'y a pas promotion...

                regex echecOuMatPion("[a-h]{1}x{1}[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, echecOuMatPion)){ // S'il y a échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(coup.substr(0,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(4,1)); // echec

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(coup.substr(0,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    
                }

            }

        }

    }
    else if(regex_match(coup, piece)){

        // 22/03/20 : pour les Pions OK, continuer pour les pièces maintenant

    }
    else if(regex_match(coup, roque)){

    }
    else{
        coup = "";
        cout << "[!] La syntaxe PGN du coup : " << coup << " étant fausse, le coup vient d'être annulé\n" << endl;
    }

}




