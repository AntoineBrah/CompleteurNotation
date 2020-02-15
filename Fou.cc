#include "Fou.h"

Fou::Fou(Couleur c, Nom n, string pos) : Piece(c,n,pos){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Fou::~Fou(){}