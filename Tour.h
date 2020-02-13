#ifndef TOUR_H
#define TOUR_H
#include "Piece.h"

class Tour : public virtual Piece{

protected:
	char skin;

public:
	Tour();
	Tour(Couleur C, Nom N);
	virtual ~Tour();
};

#endif


