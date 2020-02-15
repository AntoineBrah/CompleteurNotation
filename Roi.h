#ifndef Roi_H
#define Roi_H

#include "Piece.h"

class Roi : public virtual Piece{

protected:
	char skin;

public:
	Roi(Couleur, Nom, string);
	virtual ~Roi();
};

#endif