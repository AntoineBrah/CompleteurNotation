#ifndef Cellule_H
#define Cellule_H

#include "Piece.h"
#include "Position.h"

using namespace std;


class Cellule{

    private:
        Piece *p;
        Position* position;
        Cellule *CSP; // Coup suivant pièce
        Cellule *CSE; // Coup suivant échiquier 

    public:
        Cellule(Piece* P);

        Piece* getPiece() const;
        string getPosition()const;
        Cellule* getCSP() const;
        Cellule* getCSE() const;

        void setCSP(Cellule);
        void setCSE(Cellule);

        ~Cellule();

};

#endif