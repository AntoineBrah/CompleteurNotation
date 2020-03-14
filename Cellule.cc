#include "Cellule.h"

Cellule::Cellule(Piece* p) : piece(p), CSP(NULL), CSE(NULL), type(p->getNom()), pos(p->getPositionString()){

    for(Position pos : p->getListeCoupsPossibles()){
        listeCoupsPossibles.push_back(pos);
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

void Cellule::updateListeCoupsPossibles(){
    listeCoupsPossibles.clear();
    for(Position pos : piece->getListeCoupsPossibles()){
        listeCoupsPossibles.push_back(pos);
    }
}

void Cellule::printListeCoupsPossibles() const{

	cout << "{";

	if(listeCoupsPossibles.size() > 0){ // car erreur compilation si la liste est vide
		for(unsigned int i=0; i<=listeCoupsPossibles.size()-1; i++){

			if(i==listeCoupsPossibles.size()-1){
				cout << listeCoupsPossibles.at(i).getCoord();
			}
			else{
				cout << listeCoupsPossibles.at(i).getCoord() << ",";
			}
		}
	}

	cout << "}" << endl;
}

string Cellule::getPosition() const{
    return pos.getCoord();
}

string Cellule::getTypePiece() const{
    switch(type){
		case type::Pion : 
			return "Pion";
			break;
		case type::Tour : 
			return "Tour";
			break;
		case type::Cavalier : 
			return "Cavalier";
			break;
		case type::Fou : 
			return "Fou";
			break;
		case type::Dame : 
			return "Dame";
			break;
		case type::Roi : 
			return "Roi";
			break;
		default:
			return "Erreur";
			break;
	}
}

string Cellule::toString() const{
    return "La cellule contient :\n- Un " + this->getTypePiece() + "\n- De couleur : " + piece->getCouleur() + "\n- Dont la position est : " + pos.getCoord();
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

    for(unsigned int i=0; i<listeCoupsPossibles.size(); i++){
        if(i == listeCoupsPossibles.size()-1){
            json += listeCoupsPossibles.at(i).getCoord();
        }
        else{
            json += listeCoupsPossibles.at(i).getCoord() + " ";
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

    int cpt = 0;

    for(Cellule* cell : listeCellule){
        
        if(cell == this){
            listeCellule.erase(listeCellule.begin()+cpt);
        }

        cpt++;
    }
}

vector<Cellule*>* getListeCellule(){
	return &listeCellule;
}

Cellule* getDernierCSP(Cellule* c){

    while(c->getCSP()){
        c=c->getCSP();
    }

    return c;
}

