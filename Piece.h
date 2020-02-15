#ifndef Piece_H
#define Piece_H

#include <string>
#include "Couleur.h"

using namespace std;

enum Nom{Pion, Tour, Cavalier, Fou, Dame, Roi};


class Piece{

	protected :
		Couleur couleur;
		Nom nom;

	public :
		Piece();
		Piece(Couleur C,Nom N);
		string getCouleur() const;
		string getNom() const;
};

#endif