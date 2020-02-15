#include "Cavalier.h"

Cavalier::Cavalier(Couleur c, Nom n, string pos) : Piece(c,n,pos){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Cavalier::~Cavalier(){}