#include "Pion.h"

Pion::Pion(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}


Pion::~Pion(){}