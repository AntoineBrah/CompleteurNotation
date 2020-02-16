#include "Cellule.h"

Cellule::Cellule() : piece(NULL), pos(NULL), CSP(NULL), CSE(NULL){}
Cellule::Cellule(Piece* p) : piece(p), pos(p->getPosition()), CSP(NULL), CSE(NULL){
    /*
	if((P->getCouleur()=="Blanc") && (P->getNom()=="Pion")){
		position = "A2";
	}
	else if((P->getCouleur()=="Noir") && (P->getNom()=="Pion")){
		position = "A7";
	}
    */
}

Piece* Cellule::getPiece() const{
    return piece;
}

Cellule* Cellule::getCSP() const{
    return CSP;
}

Cellule* Cellule::getCSE() const{
    return CSE;
}

string Cellule::getPosition() const{
    return pos.getCoord();
}

string Cellule::toString() const{
    return "La cellule contient :\n- Un " + piece->getNom() + "\n- De couleur : " + piece->getCouleur() + "\n- Dont la position est ou a été : " + pos.getCoord();
}



void Cellule::setCSP(Cellule c){
    CSP=&c;
}

void Cellule::setCSE(Cellule c){
    CSE=&c;
}




Cellule::~Cellule(){}
