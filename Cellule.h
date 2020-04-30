#ifndef Cellule_H
#define Cellule_H

#include <sstream> // Permet notamment de fournir une adresse sous la forme d'une string
#include "EcritureFichier.h"
#include "Piece.h"
#include "vector"

using namespace std;

/*
*   Une pièce possède une position qui est suceptible de varier (lorsque la pièce est déplacé).
*   Une cellule possède une pièce et sa position à un instant donné dans la partie (d'ou le const).
*   Lorsqu'une cellule est créée elle possède une unique position, et chaque déplacement de pièce
*   créer une nouvelle cellule possèdant les nouvelles positions de la pièce.
*/

enum Veracite{
    Vrai = 1,
    Incertain = 0,
    Faux = -1
};

class Cellule{

    private:
        Piece *piece;
        Cellule *CSP; // Coup suivant pièce
        Cellule *CPP; // Coup précédent pièce
        Cellule *CSE; // Coup suivant échiquier  
        Cellule *CPE; // Coup précédent échiquier

        vector<vector<Position> > listeCoupsPossibles;

        const type::Nom type; // Contient le type de la pièce vers laquelle pointe la cellule (utile pour la promotion des pions)
        const Position pos; // Position de la cellule (cad de la pièce à un moment donné)

        Veracite certitude; // Certitude que l'on a sur la véracité de la cellule

    public:
        Cellule();
        Cellule(Piece*);

        static unsigned int nbErreur; // Nombre de cellules ayant val(certitude) = Faux

        Piece* getPiece();
        Cellule* getCSP() const;
        Cellule* getCPP() const;
        Cellule* getCSE() const;
        Cellule* getCPE() const;

        void updateListeCoupsPossibles();

        vector<vector<Position> >& getListeCoupsPossibles();

        void copieListeCoupsPossibles(Cellule*);

        Position getPositionCell() const;
        string getPosition() const; // Renvoi la position courante de la pièce sous la forme d'une string
        string getTypePiece() const;
        string getVeracite() const;
        
        string toString() const;

        string getJSON() const; // Renvoi toutes les infos sur la cellule au format JSON

        void setPiece(Piece*);
        void setCSP(Cellule*);
        void setCPP(Cellule*);
        void setCSE(Cellule*);
        void setCPE(Cellule*);
        void setVeracite(const Veracite);

        ~Cellule();

};

// variable globale restreinte au fichier uniquement
// cette liste nous permettra d'obtenir des informations sur toutes
// les cellules du jeu qui sont instanciées
static vector<Cellule*> listeCellule;

// renvoi un pointeur vers le vector listeCellule
// car ce vector ne peut pas être manipuler en dehors du fichier (static)
vector<Cellule*>& getListeCellule();

// renvoi la derniere cellule de CSP 
Cellule* getDernierCSP(Cellule*);

// Renvoi un pointeur contenant la cellule de la dernière pièce ayant été déplacé
Cellule* getDernierCSE();

// Renvoi un pointeur contenant la cellule de la première pièce qui s'est déplacé
Cellule* getPremierCSE();

// Renvoi le nombre de cellule de la chaine CSE depuis l'initialisation
int getStructSize();

// Permet de faire revenir la structure nbDeCSE fois en arrière
void backtrackStruct(int nbDeCSE);

#endif