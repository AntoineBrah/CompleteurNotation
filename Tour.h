#ifndef Tour_H
#define Tour_H

#include "Piece.h"

class Tour : public virtual Piece{

	public:
		Tour(Couleur, type::Nom, string);
		virtual void updateListeCoupsPossibles();
		virtual ~Tour();
};

#endif


