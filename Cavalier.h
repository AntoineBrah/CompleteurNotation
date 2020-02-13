#ifndef CAVALIER_H
#define CAVALIER_H
#include "Piece.h"

class Cavalier : public virtual Piece{

protected:
	char skin;

public:
	Cavalier();
	Cavalier(Couleur C, Nom N);
	virtual ~Cavalier();
};

#endif