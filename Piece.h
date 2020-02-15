#ifndef Piece_H
#define Piece_H

#include <string>
#include "Couleur.h"
#include "Position.h"

using namespace std;

enum Nom{Pion, Tour, Cavalier, Fou, Dame, Roi};


class Piece{

	protected :
		Couleur couleur;
		Nom nom;
		Position pos;

	public :
		Piece(Couleur, Nom, string);
		string getCouleur() const;
		string getNom() const;
		string getPosition() const;
};

#endif