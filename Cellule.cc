#include "Cellule.h"

Cellule::Cellule(Piece* p) : piece(p), CSP(NULL), CSE(NULL), pos(p->getPositionString()){

    for(unsigned int i=0; i<p->getListeCoupsPossibles()->size(); i++){
        listeCoupsPossiblesPiece.push_back(p->getListeCoupsPossibles()->at(i));
    }

    listeCellule.push_back(this);
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

string Cellule::getTypePiece() const{
    return piece->getNom();
}

string Cellule::toString() const{
    return "La cellule contient :\n- Un " + piece->getNom() + "\n- De couleur : " + piece->getCouleur() + "\n- Dont la position est : " + pos.getCoord();
}

string Cellule::getJSON() const{

    ostringstream adrCSP, adrCSE, instanceCourante;
    adrCSP << CSP;
    adrCSE << CSE;
    instanceCourante << this;

    string json = "{\"adr\":\"" + instanceCourante.str() + "\",";
    json += "\"csp\":\"" + adrCSP.str() + "\",";
    json += "\"cse\":\"" + adrCSE.str() + "\",";
    json += "\"piece\":\"" + getTypePiece() + "\",";
    json += "\"couleur\":\"" + piece->getCouleur() + "\",";
    json += "\"position\":\"" + pos.getCoord() + "\",";
    json += "\"lcp\":\""; 

    for(unsigned int i=0; i<listeCoupsPossiblesPiece.size(); i++){
        if(i == listeCoupsPossiblesPiece.size()-1){
            json += listeCoupsPossiblesPiece.at(i).getCoord();
        }
        else{
            json += listeCoupsPossiblesPiece.at(i).getCoord() + " ";
        }
    }

    json += "\"}";

    return json;
}



void Cellule::setCSP(Cellule *c){
    CSP=c;
}

void Cellule::setCSE(Cellule *c){
    CSE=c;
}

Cellule::~Cellule(){}

vector<Cellule*>* getListeCellule(){
	return &listeCellule;
}

Cellule* getDernierCSP(Cellule* c){

    while(c->getCSP()){
        c=c->getCSP();
    }

    return c;
}