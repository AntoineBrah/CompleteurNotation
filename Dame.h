#ifndef DAME_H
#define DAME_H
#include "Piece.h"

class Dame : public virtual Piece{

protected:
	char skin;

public:
	Dame();
	Dame(Couleur C, Nom N);
	virtual ~Dame();
};

#endif