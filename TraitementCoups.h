#ifndef TraitementCoups_H
#define TraitementCoups_H

#include <vector>
#include "Initialisation.h"
#include "LectureFichier.h"
#include "Piece.h"
#include "Cellule.h"
#include <iostream>

bool traitementCoups(lectureFichier*);
void seFaitMangerPiece(string pos);
void annulationSeFaitMangerPiece(Piece*,Position);

#endif