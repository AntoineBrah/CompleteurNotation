#ifndef Pion_H
#define Pion_H

#include "Piece.h"

class Pion : public virtual Piece{

	private:
		bool aBouge; // aBouge = true si le pion a déjà bougé, false sinon

	public :
		Pion(Couleur, type::Nom, string);
		virtual ~Pion();
};

#endif