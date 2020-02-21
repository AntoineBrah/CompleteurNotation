#include "Piece.h"

Piece::Piece() : couleur(Null), nom(type::Null), pos(""){}
Piece::Piece(Couleur c, type::Nom n, string p) : couleur(c), nom(n), pos(p){
	listePiece.push_back(this);
}

string Piece::getCouleur() const{
	switch(couleur){
		case Blanc : 
			return "Blanc";
			break;
		case Noir : 
			return "Noir";
			break;
		default:
			return "Null";
			break;
	}
}

string Piece::getNom() const{
	switch(nom){
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

Position Piece::getPosition() const{
	return pos;
}

string Piece::getPositionString() const{
	return pos.getCoord();
}

void Piece::setPostion(string position){
	pos.setCoord(position);
}

vector<Position>* Piece::getListeCoupsPossibles(){
	return &listeCoupsPossibles;
}

void Piece::printListeCoupsPossibles() const{

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

string Piece::toString() const{
	return "Type pièce : " + getNom() + "\nCouleur pièce : " + getCouleur() + "\nPosition pièce : " + getPositionString();
}

Piece::~Piece(){}

Piece* existePieceSurPosition(string p){
	for(unsigned int i=0; i<=listePiece.size()-1; i++){

		// On renvoit la première pièce qu'on trouve à la position donnée
		if(listePiece.at(i)->getPositionString() == p){
			return listePiece.at(i);
		}
	}

	return NULL;
}

vector<Piece*>* getListePiece(){
	return &listePiece;
}

void updateListeCoupsPossiblesAll(){
	for(unsigned int i=0; i<getListePiece()->size(); i++){
		getListePiece()->at(i)->updateListeCoupsPossibles();
	}
}