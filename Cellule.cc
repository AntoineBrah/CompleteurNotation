#include "Cellule.h"

Cellule::Cellule(Piece* p) : piece(p), CSP(NULL), CPP(NULL), CSE(NULL), type(p->getNom()), pos(p->getPositionString()){

    listeCellule.push_back(this);
}

Piece* Cellule::getPiece(){
    return piece;
}

Cellule* Cellule::getCSP() const{
    return CSP;
}

Cellule* Cellule::getCPP() const{
    return CPP;
}

Cellule* Cellule::getCSE() const{
    return CSE;
}


vector<vector<Position> >& Cellule::getListeCoupsPossibles(){
    return listeCoupsPossibles;
}

void Cellule::copieListeCoupsPossibles(Cellule *c){
    if(c != NULL){
        for(vector<Position> vect : c->getListeCoupsPossibles()){
            listeCoupsPossibles.push_back(vect);
        }
    }
}

void Cellule::updateListeCoupsPossibles(){
    // On ajoute le vector de la liste des coups possibles de la pièce vers laquelle la cellule pointe
    listeCoupsPossibles.push_back(piece->getListeCoupsPossibles());
}

Position Cellule::getPositionCell() const{
    return pos;
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

    ostringstream adrCSP, adrCPP, adrCSE, instanceCourante;
    adrCSP << CSP;
    adrCPP << CPP;
    adrCSE << CSE;
    instanceCourante << this;

    string json = "{\"adr\":\"" + instanceCourante.str() + "\",";
    json += "\"cpp\":\"" + adrCPP.str() + "\",";
    json += "\"csp\":\"" + adrCSP.str() + "\",";
    json += "\"cse\":\"" + adrCSE.str() + "\",";
    json += "\"piece\":\"" + getTypePiece() + "\",";
    json += "\"couleur\":\"" + piece->getCouleur() + "\",";
    json += "\"position\":\"" + pos.getCoord() + "\",";
    json += "\"lcp\":\""; 

    if(!listeCoupsPossibles.empty()){
        for(unsigned int i=0; i<listeCoupsPossibles.size(); i++){
            if(!listeCoupsPossibles.at(i).empty()){
                if(i != listeCoupsPossibles.size()-1){
                    for(unsigned int j=0; j<listeCoupsPossibles.at(i).size(); j++){
                        if(j != listeCoupsPossibles.at(i).size()-1){
                            json += listeCoupsPossibles.at(i).at(j).getCoord() + " ";
                        }
                        else{
                            json += listeCoupsPossibles.at(i).at(j).getCoord();
                        }
                    }
                    json += ",";
                }
                else{
                   for(unsigned int j=0; j<listeCoupsPossibles.at(i).size(); j++){
                        if(j != listeCoupsPossibles.at(i).size()-1){
                            json += listeCoupsPossibles.at(i).at(j).getCoord() + " ";
                        }
                        else{
                            json += listeCoupsPossibles.at(i).at(j).getCoord();
                        }
                    } 
                }
            }
            else{
                if(i != listeCoupsPossibles.size()-1)
                    json += ",";
            }
        }
    }

    json += "\"}";

    return json;
}


void Cellule::setPiece(Piece *p){
    piece = p;
}


void Cellule::setCSP(Cellule *c){
    CSP=c;
}

void Cellule::setCPP(Cellule *c){
    CPP=c;
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

vector<Cellule*>& getListeCellule(){
	return listeCellule;
}

Cellule* getDernierCSP(Cellule* c){

    while(c->getCSP()){
        c=c->getCSP();
    }

    return c;
}


Cellule* getDernierCSE(){
    for(Piece* p : getListePiece()){
        if(p->getFirstCell()->getCSE() != NULL){

            Cellule* c = p->getFirstCell();
            
            while(c->getCSE()){
                c=c->getCSE();
            }
            
            return c;
        }
    }
    return NULL; // C'est censé ne jamais arriver
}
