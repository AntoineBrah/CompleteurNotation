#ifndef Tour_H
#define Tour_H

#include "Piece.h"

class Tour : public virtual Piece{

protected:
	char skin;

public:
	Tour(Couleur, Nom, string);
	virtual ~Tour();
};

#endif


