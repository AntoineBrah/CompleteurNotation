#ifndef Cellule_H
#define Cellule_H
using namespace std;
#include "Piece.h"

class Cellule{

    private:
        Piece *p;
        string position;
        Cellule *CSP; // Coup suivant pièce
        Cellule *CSE; // Coup suivant échiquier 

    public:
        Cellule();
        Cellule(Couleur, Nom);

        Piece* getPiece() const;
        string getPosition()const;
        Cellule* getCSP() const;
        Cellule* getCSE() const;

        void setCSP(Cellule);
        void setCSE(Cellule);

        ~Cellule();

};

#endif