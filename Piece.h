#ifndef Piece_H
#define Piece_H

#include <vector>
#include <string>
#include <cmath>
#include "Couleur.h"
#include "Position.h"
#include "Point.h"

using namespace std;

namespace type{
	enum Nom{
		Null,
		Pion, 
		Tour, 
		Cavalier, 
		Fou, 
		Dame, 
		Roi
	};
}

/*
* Pièce est une classe abstraite, de fait elle ne peut pas être instancié
*/

class Piece;
class Cellule;

#include "Cellule.h"

class Piece{

	protected :
		Couleur couleur;
		type::Nom nom;
		Position pos;
		vector<Position> listeCoupsPossibles;
		bool aBouge; // true si la pièce a déjà bougé, false sinon
		Cellule* firstCell;

	public :
		Piece();
		Piece(Couleur, type::Nom, string);

		string getCouleur() const;
		type::Nom getNom() const;
		string getNomString() const;
		Position getPosition() const; // Renvoi la position de la pièce
		string getPositionString() const; // Renvoi la position de la pièce sous forme de string
		bool getABouge() const; // Renvoi true si une pièce a déjà bougé, false sinon
		Cellule* getFirstCell() const; // Renvoi l'adresse de la première cellule de la pièce

		virtual void updateListeCoupsPossibles() = 0; // Méthode (abstraite) virtuelle pure

		void setFirstCell(Cellule*);
		void setPostion(string);
		void setNom(string);
		vector<Position>& getListeCoupsPossibles(); // Renvoi un pointeur vers la liste des coups possibles d'une pièce
		void printListeCoupsPossibles() const;
		void supprimePosDeLCP(const Position&); // Supprime la position de la liste des coups possibles de la pièce

		string toString() const;
		
		virtual ~Piece();
};

// variable globale restreinte au fichier uniquement
// cette liste nous permettra d'obtenir des informations sur toutes
// les pièces du jeu qui sont instanciés
static vector<Piece*> listePiece;

// renvoi un pointeur vers le vector listePiece
// car ce vector ne peut pas être manipuler en dehors du fichier (static)
vector<Piece*>& getListePiece();

// fonction qui prend en parametre une position et renvoi la première pièce présente sur cette position
// renvoi NULL si aucune pièce présente sur la position donnée

/*
* On test l'existance d'une piece de la manière suivante : if(existePieceSurPosition("a2")),
* si on souhaite tester la non existance, il suffit de faire la négation : if(!existePieceSurPosition("a2"))
* Si la pièce existe sur la position donnée :
* 	existePieceSurPosition(pos) renvoit l'adresse de la pièce (<=> true dans un if(existePieceSurPosition(...)))
*	!existePieceSurPosition(pos) renvoit 0
* Si la pièce n'existe pas sur la position donnée :
*	existePieceSurPosition(pos) renvoit 0 
*	!existePieceSurPosition(pos) renvoit 1
*/
Piece* existePieceSurPosition(string);

// renvoi true si la position fait parti de la liste des coups possibles de la pièce, renvoi false sinon
bool appartientLCP(Piece*, string position);

// Met à jour la liste des coups possibles de toutes les pièces instanciés
void updateListeCoupsPossiblesAll(bool);

#endif