#ifndef GestionErreurs_h
#define GestionErreurs_h

#include "Piece.h"
#include "Roi.h"
#include "TraitementCoups.h"
#include <iomanip>

using namespace std;


void verificationDeplacementPiece(Cellule* &,string, string, vector<string>&, int, lectureFichier*);
void deplacementPiece(Piece*, Cellule* &,string, string, vector<string>&, int);

//Ingo a rajouté ceci//
void coupOublie(Cellule* cell);
int PartieJuste(Cellule* cell);
void affichagePartieJuste(Cellule* cell);
//Ingo a rajouté ceci//


#endif