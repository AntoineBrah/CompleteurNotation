#ifndef Dame_H
#define Dame_H

#include "Piece.h"

class Dame : public virtual Piece{

	public:
		Dame(Couleur, type::Nom, string);
		virtual void updateListeCoupsPossibles();
		virtual ~Dame();
		static int nbInstances;
};

#endif