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

string Piece::getPosition() const{
	return pos.getCoord();
}