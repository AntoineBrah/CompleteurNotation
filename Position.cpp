#include "Position.h"

Position::Position() : colonne(""), ligne(","){}

Position::Position(string pos) : colonne(""), ligne(""){

    if(pos.size() != 2 && pos != "NULL"){
        cout << "ERREUR la position doit contenir uniquement 2 caractères de la forme : [Colonne][Ligne]." << endl;
    }
    else if(pos == "NULL"){
        colonne = "NU";
        ligne = "LL";
    }
    else if (((pos[0] != 'a') && (pos[0] != 'b') && (pos[0] != 'c') && (pos[0] != 'd') && (pos[0] != 'e') && (pos[0] != 'f') && (pos[0] != 'g') && (pos[0] != 'h')) 
    || ((pos[1] != '1') && (pos[1] != '2') && (pos[1] != '3') && (pos[1] != '4') && (pos[1] != '5') && (pos[1] != '6') && (pos[1] != '7') && (pos[1] != '8'))){

        cout << "ERREUR la valeur de [Colonne] est compris entre : [a-h] et la valeur de ligne entre : [1-8]" << endl;
    }
    else{

        int li = (int)pos[1];

        if((pos[0] == 'a' || pos[0] == 'c' || pos[0] == 'e' || pos[0] == 'g')){
            if((li != 0) && (li%2 == 0)){
                couleurCase = Blanc; 
                colonne = pos[0];
                ligne = pos[1];
            }
            else{
                couleurCase = Noir;
                colonne = pos[0];
                ligne = pos[1]; 
            }
        }
        else if((pos[0] == 'b' || pos[0] == 'd' || pos[0] == 'f' || pos[0] == 'h')){
            if((li != 0) && (li%2 == 0)){
                couleurCase = Noir;
                colonne = pos[0];
                ligne = pos[1];
            }
            else{
                couleurCase = Blanc; 
                colonne = pos[0];
                ligne = pos[1];
            }
        }
        else{
            cout << "ERREUR";
        }
    }
}


void Position::setCoord(string pos){
    if(pos.size() != 2 && pos != "NULL"){
        cout << "ERREUR la position doit contenir uniquement 2 charactères de la forme : [Colonne][Ligne]." << endl;
    }
    else if(pos == "NULL"){
        colonne = "NU";
        ligne = "LL";
    }
    else if (((pos[0] != 'a') && (pos[0] != 'b') && (pos[0] != 'c') && (pos[0] != 'd') && (pos[0] != 'e') && (pos[0] != 'f') && (pos[0] != 'g') && (pos[0] != 'h')) 
    || ((pos[1] != '1') && (pos[1] != '2') && (pos[1] != '3') && (pos[1] != '4') && (pos[1] != '5') && (pos[1] != '6') && (pos[1] != '7') && (pos[1] != '8'))){

        cout << "ERREUR la valeur de [Colonne] est compris entre : [a-h] et la valeur de ligne entre : [1-8]" << endl;
    }
    else{
        colonne = pos[0];
        ligne = pos[1];
    }
}

string Position::getCoord() const{
    return colonne+ligne;
}

string Position::getCouleur() const{
    switch(couleurCase){
		case Blanc : 
			return "Blanche";
			break;
		case Noir : 
			return "Noire";
			break;
		default:
			return "Erreur";
			break;
	}
}

string Position::getColonne() const{
    return colonne;
}

string Position::getLigne() const{
    return ligne;
}

string Position::toString() const{
    return "Coordonnées : " + this->getCoord() + "\nCouleur : " + this->getCouleur();
}