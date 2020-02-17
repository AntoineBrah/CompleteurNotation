#include "Piece.h"

Piece::Piece() : couleur(Null), nom(type::Null), pos(""){}
Piece::Piece(Couleur c, type::Nom n, string p) : couleur(c), nom(n), pos(p){}

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

void Piece::printListeCoupsPossibles() const{

	cout << "{";

	for(unsigned int i=0; i<=listeCoupsPossibles.size()-1; i++){

		if(i==listeCoupsPossibles.size()-1){
			cout << listeCoupsPossibles.at(i).getCoord();
		}
		else{
			cout << listeCoupsPossibles.at(i).getCoord() << ",";
		}
	}

	cout << "}" << endl;
}

string Piece::toString() const{
	return "Type pièce : " + getNom() + "\nCouleur pièce : " + getCouleur() + "\nPosition pièce : " + getPositionString();
}