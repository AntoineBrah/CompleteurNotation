#ifndef Piece_H
#define Piece_H

#include <vector>
#include <string>
#include "Couleur.h"
#include "Position.h"
#include "Point.h"

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
		vector<Position> listeCoupsPossibles;

	public :
		Piece();
		Piece(Couleur, type::Nom, string);
		string getCouleur() const;
		string getNom() const;
		string getPosition() const;

		void setPostion(string);
		void printListeCoupsPossibles() const;

		string toString() const;
};



#endif