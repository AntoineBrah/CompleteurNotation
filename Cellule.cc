#include "Cellule.h"

Cellule::Cellule(Piece* p) : piece(p), CSP(NULL), CSE(NULL), pos(p->getPositionString()){}

Piece* Cellule::getPiece() const{
    return piece;
}

Cellule* Cellule::getCSP() const{
    return CSP;
}

Cellule* Cellule::getCSE() const{
    return CSE;
}

string Cellule::getPositionPiece() const{
    return pos.getCoord();
}

string Cellule::getTypePiece() const{
    return piece->getNom();
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
