#include "Roi.h"

Roi::Roi(Couleur c, Nom n, string pos) : Piece(c,n,pos){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Roi::~Roi(){}