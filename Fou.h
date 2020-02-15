#ifndef Fou_H
#define Fou_H

#include "Piece.h"

class Fou : public virtual Piece{

protected:
	char skin;

public:
	Fou(Couleur, type::Nom, string);
	virtual ~Fou();
};

#endif