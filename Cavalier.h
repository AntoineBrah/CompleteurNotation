#ifndef Cavalier_H
#define Cavalier_H

#include "Piece.h"

class Cavalier : public virtual Piece{

protected:
	char skin;

public:
	Cavalier(Couleur, type::Nom, string);
	virtual ~Cavalier();
};

#endif