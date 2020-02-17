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

		virtual void updateListeCoupsPossibles() = 0;

	public :
		Piece();
		Piece(Couleur, type::Nom, string);
		string getCouleur() const;
		string getNom() const;
		Position getPosition() const; // Renvoi la position de la pièce
		string getPositionString() const; // Renvoi la position de la pièce sous forme de string

		void setPostion(string);
		void printListeCoupsPossibles() const;

		string toString() const;
};



#endif