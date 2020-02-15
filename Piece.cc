
#include "Piece.h"

Piece::Piece(){}

Piece::Piece(Couleur C, Nom N) : couleur(C), nom(N){
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
			return "Erreur";
			break;
	}
}

string Piece::getNom() const{
	switch(nom){
		case Pion : 
			return "Pion";
			break;
		case Tour : 
			return "Tour";
			break;
		case Cavalier : 
			return "Cavalier";
			break;
		case Fou : 
			return "Fou";
			break;
		case Dame : 
			return "Dame";
			break;
		case Roi : 
			return "Roi";
			break;
		default:
			return "Erreur";
			break;
	}
}