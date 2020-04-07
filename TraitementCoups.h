#ifndef TraitementCoups_H
#define TraitementCoups_H

#include <vector>
#include "Initialisation.h"
#include "LectureFichier.h"
#include "Piece.h"
#include "Cellule.h"
#include "GestionErreurs.h"
#include <iostream>


bool analyseCoups(string path); // Analyse la partie (celle qui contient les erreurs)
bool traitementCoups(string path); // Corrige la partie
void seFaitMangerPiece(Piece*);
void annulationSeFaitMangerPiece(Piece*,Position);

#endif