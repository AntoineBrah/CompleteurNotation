#ifndef Pion_H
#define Pion_H

#include "Piece.h"

class Pion : public virtual Piece{

	protected :
		char skin;
		
	public :
		Pion(Couleur, type::Nom, string);
		virtual ~Pion();
};

#endif