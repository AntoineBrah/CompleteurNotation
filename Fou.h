#ifndef FOU_H
#define FOU_H
#include "Piece.h"

class Fou : public virtual Piece{

protected:
	char skin;

public:
	Fou();
	Fou(Couleur C, Nom N);
	virtual ~Fou();
};

#endif