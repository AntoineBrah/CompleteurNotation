#ifndef Piece_H
#define Piece_H

#include <string>
#include "Couleur.h"
#include "Position.h"

using namespace std;

namespace type{
	enum Nom{
		Null,
		Pion, 
		Tour, 
		Cavalier, 
		Fou, 
		Dame, 
		Roi
	};
}


class Piece{

	protected :
		Couleur couleur;
		type::Nom nom;
		Position pos;

	public :
		Piece();
		Piece(Couleur, type::Nom, string);
		string getCouleur() const;
		string getNom() const;
		string getPosition() const;
};

#endif