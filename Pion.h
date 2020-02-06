#ifndef PION_H
#define PION_H
#include <list>
using namespace std;
#include "Piece.h"

class pion : public virtual Piece{

	protected :
		char skin;
		
	public :
		pion();
		pion(Couleur C,Nom N);
		//virtual vector<string> mouvement();
};

#endif