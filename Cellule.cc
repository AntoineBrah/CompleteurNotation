#include "Cellule.h"

Cellule::Cellule() : p(NULL),position(""), CSP(NULL), CSE(NULL){}
Cellule::Cellule(Couleur c, Nom n) : 
p(new Piece(c, n)),position(""), CSP(NULL), CSE(NULL){}

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
