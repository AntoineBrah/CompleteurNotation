#ifndef ROI_H
#define ROI_H
#include "Piece.h"

class Roi : public virtual Piece{

protected:
	char skin;

public:
	Roi();
	Roi(Couleur C, Nom N);
	virtual ~Roi();
};

#endif