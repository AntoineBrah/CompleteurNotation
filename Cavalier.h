#ifndef Cavalier_H
#define Cavalier_H

#include "Piece.h"

class Cavalier : public virtual Piece{

	public:
		Cavalier(Couleur, type::Nom, string);
		virtual ~Cavalier();
};

#endif