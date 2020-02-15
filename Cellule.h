#ifndef Cellule_H
#define Cellule_H

#include "Piece.h"

using namespace std;


class Cellule{

    private:
        Piece *p;
        Cellule *CSP; // Coup suivant pièce
        Cellule *CSE; // Coup suivant échiquier 

    public:
        Cellule(Piece* P);

        Piece* getPiece() const;
        Cellule* getCSP() const;
        Cellule* getCSE() const;
        string getPositionPiece() const;

        void setCSP(Cellule);
        void setCSE(Cellule);

        ~Cellule();

};

#endif