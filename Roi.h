#ifndef Roi_H
#define Roi_H

#include "Piece.h"

class Roi : public virtual Piece{
	public:
		Roi(Couleur, type::Nom, string);
		virtual void updateListeCoupsPossibles();

		/*
		* On va s'assurer qu'aucune pièce adverse ne possède dans sa liste des 
		* coups possibles, la position ou le Roi souhaite se déplacer.
		* Ceci permet d'éviter que le Roi se mette tout seul en échec.
		*/
		bool posDansLCPAdverse(const string&) const;

		/*
		* Méthode relative au Problème n°1 voir : 'Probleme/Probleme1/explication.txt'
		* Résumé : le Roi détermine s'il peut se déplacer sur une case sous 2 conditions :
		*      - Ça respecte son déplacement (se déplacer d'1 seule case)
			- Aucune pièce adverse ne possède dans sa listeDeCoupsPossibles les cases 
				auxquelles le Roi souhaite se déplacer.
		* En gros comme un Pion ne possède pas dans sa listeCoupsPossibles ses
		* diagonales si aucune pièce adverse n'est présente sur ces positons, alors le Roi
		* croit qu'il peut se déplacer alors qu'il ne peut pas car sinon il se retrouve en
		* échec.
		*
		* L'objectif de cette fonction inhérante au Roi est d'obtenir les diagonales supérieures
		* d'une position donnée afin de déterminer quels pions y sont positionnés et ainsi savoir
		* s'il s'agit de Pions adverses ou non.
		*
		* La méthode sert juste a éviter de faire une série de calcul...
		*/

		bool possedePionAdverseEnDiagonaleSup(const Point&);

		virtual ~Roi();
};

bool estEnEchecRoi(string Couleur);

#endif