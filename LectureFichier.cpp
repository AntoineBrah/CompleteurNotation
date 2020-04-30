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
        cout << fichier << " : ouverture en lecture échouée." << endl << endl;
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

string lectureFichier::getLigne() const{
  return ligne;
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
    
    if(pos != -1)
        cb = s.substr(0,pos);
    else
        cb = s;

    detecterCoup(cb, descriptionCb, "Blanc");

    // Cas ou il n'y a pas d'espace et donc on finit avec un coup blanc
    if(pos == -1){
        cn = "";

        detecterCoup(cn, descriptionCn, "Noir");
    }
    else{
        cn = s.substr(pos+1); // si on précise pas le deuxième paramètre, ça va jusqu'à la fin de la chaine

        detecterCoup(cn, descriptionCn, "Noir");
    }
}

ifstream* lectureFichier::getFlux(){
    return &monFlux;
}

vector<string>& lectureFichier::getDescriptionCb(){
    return descriptionCb;
}

vector<string>& lectureFichier::getDescriptionCn(){
    return descriptionCn;
}

lectureFichier::~lectureFichier(){
    monFlux.close();
}


void detecterCoup(string &coup, vector<string> &description, string couleurPiece){

    description.clear();


    regex pion("[a-h]?x?[a-h]{1}[1-8]{1}(=[DFCT])?[+#]?"); // regex pour un pion
    regex piece("[RDFCT]{1}[a-h1-8]?x?[a-h]{1}[1-8]{1}[+#]?"); // regex pour une piece
    regex roque("O-O(-O)?"); // regex pour le roque


    if(regex_match(coup, pion) && !regex_match(coup, regex("x{1}[a-h]{1}[1-8]{1}(=[DFCT])?[+#]?")) && !regex_match(coup, regex("[a-h]{1}[a-h]{1}[1-8]{1}(=[DFCT])?[+#]?"))){
        
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
                    description.push_back(""); // Mange une pièce

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(0,2)); // Déplacement
                    description.push_back(coup.substr(2,2)); // Promotion
                    description.push_back(""); // echec
                    description.push_back(""); // Mange une pièce
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
                    description.push_back(""); // Mange une pièce

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(0,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back(""); // Mange une pièce
                    
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
                    description.push_back("x"); // Mange une pièce

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(coup.substr(0,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(coup.substr(4,2)); // Promotion
                    description.push_back(""); // echec
                    description.push_back("x"); // Mange une pièce
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
                    description.push_back("x"); // Mange une pièce

                }
                else{ // S'il n'y a pas échec ou mat

                    description.push_back("Pion"); // Piece
                    description.push_back(coup.substr(0,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back("x"); // Mange une pièce
                    
                }

            }

        }

    }
    else if(regex_match(coup, piece)){

        regex deplacementPiece("[RDFCT]{1}[a-h1-8]?[a-h]{1}[1-8]{1}[+#]?");
        regex mangePiece("[RDFCT]{1}[a-h1-8]?x{1}[a-h]{1}[1-8]{1}[+#]?");

        string typePiece = "NULL";

        switch(coup[0]){
            case 'T':
                typePiece = "Tour";
                break;
            case 'C':
                typePiece = "Cavalier";
                break;
            case 'F':
                typePiece = "Fou";
                break;
            case 'D':
                typePiece = "Dame";
                break;
            case 'R':
                typePiece = "Roi";
                break;
            default:
                cout << "ERREUR : Impossible de déterminer de quelle pièce il s'agit." << endl;
                break;
        }



        if(regex_match(coup, deplacementPiece)){ // Si la pièce ne fait que se déplacer

            regex deplacementPieceLigne("[RDFCT]{1}[1-8]{1}[a-h]{1}[1-8]{1}[+#]?"); // 2 pièce sur la même colonne se déplace sur la même case
            regex deplacementPieceColonne("[RDFCT]{1}[a-h]{1}[a-h]{1}[1-8]{1}[+#]?"); // 2 pièce sur la même ligne se déplace sur la même case
            regex deplacementPieceAucun("[RDFCT]{1}[a-h]{1}[1-8]{1}[+#]?"); // Aucune ambigüité

            if(regex_match(coup, deplacementPieceLigne)){ 

                regex deplacementPieceLigneEchecOuMat("[RDFCT]{1}[1-8]{1}[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, deplacementPieceLigneEchecOuMat)){ // S'il y a échec ou mat
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(coup.substr(1,1)); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(4,1)); // echec
                    description.push_back(""); // Mange une pièce
                }
                else{ // S'il n'y a ni échec ni mat
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(coup.substr(1,1)); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back(""); // Mange une pièce
                }


            }
            else if(regex_match(coup, deplacementPieceColonne)){
                
                regex deplacementPieceColonneEchecOuMat("[RDFCT]{1}[a-h]{1}[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, deplacementPieceColonneEchecOuMat)){ // S'il y a échec ou mat
                    description.push_back(typePiece); // Piece
                    description.push_back(coup.substr(1,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(4,1)); // echec
                    description.push_back(""); // Mange une pièce
                }
                else{ // S'il n'y a ni échec ni mat
                    description.push_back(typePiece); // Piece
                    description.push_back(coup.substr(1,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back(""); // Mange une pièce
                }

            }
            else if(regex_match(coup, deplacementPieceAucun)){

                regex deplacementPieceAucunEchecOuMat("[RDFCT]{1}[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, deplacementPieceAucunEchecOuMat)){ // S'il y a échec ou mat
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(1,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(3,1)); // echec
                    description.push_back(""); // Mange une pièce
                }
                else{ // S'il n'y a pas échec ou mat 
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(1,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back(""); // Mange une pièce
                }
            }

        }
        else if(regex_match(coup, mangePiece)){ // Si la pièce mange une autre pièce

            regex deplacementPieceLigne("[RDFCT]{1}[1-8]{1}x{1}[a-h]{1}[1-8]{1}[+#]?"); // 2 pièce sur la même colonne se déplace sur la même case
            regex deplacementPieceColonne("[RDFCT]{1}[a-h]{1}x{1}[a-h]{1}[1-8]{1}[+#]?"); // 2 pièce sur la même ligne se déplace sur la même case
            regex deplacementPieceAucun("[RDFCT]{1}x{1}[a-h]{1}[1-8]{1}[+#]?"); // Aucune ambigüité

            if(regex_match(coup, deplacementPieceLigne)){ 

                regex deplacementPieceLigneEchecOuMat("[RDFCT]{1}[1-8]{1}x{1}[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, deplacementPieceLigneEchecOuMat)){ // S'il y a échec ou mat
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(coup.substr(1,1)); // Ligne
                    description.push_back(coup.substr(3,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(5,1)); // echec
                    description.push_back("x"); // Mange une pièce
                }
                else{ // S'il n'y a ni échec ni mat
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(coup.substr(1,1)); // Ligne
                    description.push_back(coup.substr(3,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back("x"); // Mange une pièce
                }


            }
            else if(regex_match(coup, deplacementPieceColonne)){
                
                regex deplacementPieceColonneEchecOuMat("[RDFCT]{1}[a-h]{1}x{1}[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, deplacementPieceColonneEchecOuMat)){ // S'il y a échec ou mat
                    description.push_back(typePiece); // Piece
                    description.push_back(coup.substr(1,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(3,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(5,1)); // echec
                    description.push_back("x"); // Mange une pièce
                }
                else{ // S'il n'y a ni échec ni mat
                    description.push_back(typePiece); // Piece
                    description.push_back(coup.substr(1,1)); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(3,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back("x"); // Mange une pièce
                }

            }
            else if(regex_match(coup, deplacementPieceAucun)){

                regex deplacementPieceAucunEchecOuMat("[RDFCT]{1}x{1}[a-h]{1}[1-8]{1}[+#]{1}");

                if(regex_match(coup, deplacementPieceAucunEchecOuMat)){ // S'il y a échec ou mat
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(coup.substr(4,1)); // echec
                    description.push_back("x"); // Mange une pièce
                }
                else{ // S'il n'y a pas échec ou mat 
                    description.push_back(typePiece); // Piece
                    description.push_back(""); // Colonne
                    description.push_back(""); // Ligne
                    description.push_back(coup.substr(2,2)); // Déplacement
                    description.push_back(""); // Promotion
                    description.push_back(""); // echec
                    description.push_back("x"); // Mange une pièce
                }
            }

        }
        

    }
    else if(regex_match(coup, roque)){

        regex petitRoque("O-O");
        regex grandRoque("O-O-O");

        if(couleurPiece == "Blanc"){

            if(regex_match(coup, petitRoque)){
                description.push_back("Roi"); // Piece
                description.push_back(""); // Colonne
                description.push_back(""); // Ligne
                description.push_back("g1"); // Déplacement
                description.push_back(""); // Promotion
                description.push_back(""); // echec
                description.push_back(""); // Mange une pièce
            }
            else if(regex_match(coup, grandRoque)){
                description.push_back("Roi"); // Piece
                description.push_back(""); // Colonne
                description.push_back(""); // Ligne
                description.push_back("c1"); // Déplacement
                description.push_back(""); // Promotion
                description.push_back(""); // echec
                description.push_back(""); // Mange une pièce
            }
        }
        else if(couleurPiece == "Noir"){

            if(regex_match(coup, petitRoque)){
                description.push_back("Roi"); // Piece
                description.push_back(""); // Colonne
                description.push_back(""); // Ligne
                description.push_back("g8"); // Déplacement
                description.push_back(""); // Promotion
                description.push_back(""); // echec
                description.push_back(""); // Mange une pièce
            }
            else if(regex_match(coup, grandRoque)){
                description.push_back("Roi"); // Piece
                description.push_back(""); // Colonne
                description.push_back(""); // Ligne
                description.push_back("c8"); // Déplacement
                description.push_back(""); // Promotion
                description.push_back(""); // echec
                description.push_back(""); // Mange une pièce
            }
        }
        
    }
    //Ingo à rajouté ceci//
    else if(coup == "_"){
      description.push_back("Null"); // Piece
      description.push_back(""); // Colonne
      description.push_back(""); // Ligne
      description.push_back(""); // Déplacement
      description.push_back(""); // Promotion
      description.push_back(""); // echec
      description.push_back(""); // Mange une pièce
    }
    //Ingo à rajouté ceci//
    else{
        //cout << "[!] La syntaxe PGN du coup : '" << coup << "' étant fausse, le coup vient d'être annulé.\n" << endl;
        coup = "";
    }

    if(coup != ""){
        //separator();
        //cout << "Piece : " << description[0] << "\nColonne : " << description[1] << "\nLigne : " << description[2] << "\nDéplacement : " << description[3] << "\nPromotion : " << description[4] << "\nEchec ou mat : " << description[5] << endl;
        //separator();
    }

}

