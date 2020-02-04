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

Nom Piece::getNom() const{
	return nom;
}