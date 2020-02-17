#ifndef Fou_H
#define Fou_H

#include "Piece.h"

class Fou : public virtual Piece{

	public:
		Fou(Couleur, type::Nom, string);
		virtual void updateListeCoupsPossibles();
		virtual ~Fou();
};

#endif