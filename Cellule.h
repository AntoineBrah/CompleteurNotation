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
        Cellule *CSP; // Coup suivant pièce
        Cellule *CSE; // Coup suivant échiquier 

    public:
        Cellule(Piece*);

        const Position pos; // Position de la cellule (cad de la pièce à un moment donné)

        Piece* getPiece() const;
        Cellule* getCSP() const;
        Cellule* getCSE() const;
        string getPositionPiece() const; // Renvoi la position courante de la pièce
        string getTypePiece() const;
        
        string toString() const;

        void setCSP(Cellule);
        void setCSE(Cellule);

        ~Cellule();

};

#endif