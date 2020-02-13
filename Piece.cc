
#include "Piece.h"

Piece::Piece(){}

Piece::Piece(Couleur C, Nom N) : couleur(C), nom(N){
}

string Piece::getCouleur() const{
	switch(couleur){
		case Blanc : return "Blanc";
		case Noir : return "Noir";
	}
}

string Piece::getNom() const{
	switch(nom){
		case Pion : return "Pion";
		case Tour : return "Tour";
		case Cavalier : return "Cavalier";
		case Fou : return "Fou";
		case Dame : return "Dame";
		case Roi : return "Roi";
	}
}