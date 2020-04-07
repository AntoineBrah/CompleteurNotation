#ifndef GestionErreurs_h
#define GestionErreurs_h

#include "Piece.h"
#include "Roi.h"
#include "TraitementCoups.h"

using namespace std;


void verificationDeplacementPiece(Cellule* &,string, string, vector<string>&, int);
void deplacementPiece(Piece*, Cellule* &,string, string, vector<string>&, int);


#endif