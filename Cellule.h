#ifndef Cellule_H
#define Cellule_H

#include "Piece.h"

using namespace std;

/*
*   Une pièce possède une position qui est suceptible de varier (lorsque la pièce est déplacé).
*   Une cellule possède une pièce et sa position à un instant donné dans la partie (d'ou le const).
*   Lorsqu'une cellule est créée elle possède une unique position, et chaque déplacement de pièce
*   créer une nouvelle cellule possèdant les nouvelles positions de la pièce.
*/

class Cellule{

    private:
        Piece *piece;
        const Position pos;
        Cellule *CSP; // Coup suivant pièce
        Cellule *CSE; // Coup suivant échiquier 

    public:
        Cellule(Piece*);

        Piece* getPiece() const;
        Cellule* getCSP() const;
        Cellule* getCSE() const;
        string getPosition() const;
        string toString() const;

        void setCSP(Cellule);
        void setCSE(Cellule);

        ~Cellule();

};

#endif