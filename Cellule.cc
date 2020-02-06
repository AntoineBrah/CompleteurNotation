#include "Cellule.h"

Cellule::Cellule() : p(NULL),position(""), CSP(NULL), CSE(NULL){}
Cellule::Cellule(Piece* P) : p(P), CSP(NULL), CSE(NULL){
	if((P->getCouleur()=="Blanc") && (P->getNom()=="Pion")){
		position = "A2";
	}
	else if((P->getCouleur()=="Noir") && (P->getNom()=="Pion")){
		position = "A7";
	}
}

Piece* Cellule::getPiece() const{
    return p;
}

string Cellule::getPosition() const{
    return position;
}

Cellule* Cellule::getCSP() const{
    return CSP;
}

Cellule* Cellule::getCSE() const{
    return CSE;
}

void Cellule::setCSP(Cellule c){
    CSP=&c;
}

void Cellule::setCSE(Cellule c){
    CSE=&c;
}

Cellule::~Cellule(){}
