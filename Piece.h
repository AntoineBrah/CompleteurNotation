#ifndef PIECE_H
#define PIECE_H
#include<string>
using namespace std;

enum Couleur{Blanc, Noir};
enum Nom{Pion, Tour, Cavalier, Fou, Dame, Roi};


class Piece{

	protected :
		Couleur couleur;
		Nom nom;

	public :
		Piece();
		Piece(Couleur C,Nom N);
		virtual string getCouleur()const;
		virtual string getNom()const;
};

#endif