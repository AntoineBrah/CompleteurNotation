#include "Cellule.h"

Cellule::Cellule(Piece* p) : piece(p), CSP(NULL), CSE(NULL), pos(p->getPositionString()){
    listeCellule.push_back(this);
    ecritureFichier(this->getJSON() + ","); // On ajoute les infos de la cellule dans le fichier
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

string Cellule::getPositionPiece() const{
    return pos.getCoord();
}

string Cellule::getTypePiece() const{
    return piece->getNom();
}

string Cellule::toString() const{
    return "La cellule contient :\n- Un " + piece->getNom() + "\n- De couleur : " + piece->getCouleur() + "\n- Dont la position est : " + pos.getCoord();
}

string Cellule::getJSON() const{
    string json = "{\"type\":\"Cellule\",";
    json += "\"piece\":\"" + getTypePiece() + "\",";
    json += "\"couleur\":\"" + piece->getCouleur() + "\",";
    json += "\"position\":\"" + pos.getCoord() + "\",";
    json += "\"lcp\":\""; 

    for(unsigned int i=0; i<piece->getListeCoupsPossibles()->size(); i++){
        if(i == piece->getListeCoupsPossibles()->size()-1){
            json += piece->getListeCoupsPossibles()->at(i).getCoord();
        }
        else{
            json += piece->getListeCoupsPossibles()->at(i).getCoord() + " ";
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

Cellule::~Cellule(){
    delete piece; // Effacer la cellule efface d'abord la pièce qu'elle contient
}

vector<Cellule*>* getListeCellule(){
	return &listeCellule;
}

Cellule* getDernierCSP(Cellule* c){
    return c->getCSP() != NULL? getDernierCSP(c->getCSP()):c;
}