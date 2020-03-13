#ifndef Cellule_H
#define Cellule_H

#include <sstream> // Permet notamment de fournir une adresse sous la forme d'une string
#include "EcritureFichier.h"
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

        vector<Position> listeCoupsPossiblesPiece;

    public:
        Cellule(Piece*);

        const type::Nom type; // Contient le type de la pièce vers laquelle pointe la cellule (utile pour la promotion des pions)
        const Position pos; // Position de la cellule (cad de la pièce à un moment donné)

        Piece* getPiece() const;
        Cellule* getCSP() const;
        Cellule* getCSE() const;

        vector<Position>* getListeCoupsPossiblesPiece();
        void printListeCoupsPossiblesPiece() const;

        string getPosition() const; // Renvoi la position courante de la pièce
        string getTypePiece() const;
        
        string toString() const;

        string getJSON() const; // Renvoi toutes les infos sur la cellule au format JSON

        void setCSP(Cellule*);
        void setCSE(Cellule*);

        ~Cellule();

};

// variable globale restreinte au fichier uniquement
// cette liste nous permettra d'obtenir des informations sur toutes
// les cellules du jeu qui sont instanciés
static vector<Cellule*> listeCellule;

// renvoi un pointeur vers le vector listeCellule
// car ce vector ne peut pas être manipuler en dehors du fichier (static)
vector<Cellule*>* getListeCellule();


// renvoi la derniere cellule de CSP 
Cellule* getDernierCSP(Cellule*);

// Met la position à NULL (en dehors du plateau) de la pièce qui se fait manger
// Et renvoi un pointeur vers une nouvelle Cellule (que l'on chaine à la liste CSP de la pièce qui se fait manger) avec les valeurs CSP,CSE,Position toutes à NULL
void seFaitMangerPiece(string pos);

#endif