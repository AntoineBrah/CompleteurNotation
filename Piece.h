#ifndef Piece_H
#define Piece_H

#include <vector>
#include <string>
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


class Piece{

	protected :
		Couleur couleur;
		type::Nom nom;
		Position pos;
		vector<Position> listeCoupsPossibles;

		virtual void updateListeCoupsPossibles() = 0; // Méthode (abstraite) virtuelle pure

	public :
		Piece();
		Piece(Couleur, type::Nom, string);
		string getCouleur() const;
		string getNom() const;
		Position getPosition() const; // Renvoi la position de la pièce
		string getPositionString() const; // Renvoi la position de la pièce sous forme de string

		void setPostion(string);
		void printListeCoupsPossibles() const;

		string toString() const;
		
		virtual ~Piece();
};

// variable globale restreinte au fichier uniquement
// cette liste nous permettra d'obtenir des informations sur toutes
// les pièces du jeu qui sont instanciés
static vector<Piece*> listePiece;

// fonction qui prend en parametre une position et renvoi la première pièce présente sur cette position
// renvoi NULL si aucune pièce présente sur la position donnée

/*
* On test l'existance d'une piece de la manière suivante : if(existePieceSurPosition("a2")),
* si on souhaite tester la non existance, il suffit de faire la négation : if(!existePieceSurPosition("a2"))
*/
Piece* existePieceSurPosition(string);


#endif