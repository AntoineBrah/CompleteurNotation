#ifndef Roi_H
#define Roi_H

#include "Piece.h"

class Roi : public virtual Piece{
	public:
		Roi(Couleur, type::Nom, string);
		virtual void updateListeCoupsPossibles();
		virtual ~Roi();
};

#endif