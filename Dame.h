#ifndef Dame_H
#define Dame_H

#include "Piece.h"

class Dame : public virtual Piece{

protected:
	char skin;

public:
	Dame(Couleur, Nom, string);
	virtual ~Dame();
};

#endif