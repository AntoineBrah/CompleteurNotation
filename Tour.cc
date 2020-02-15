#include "Tour.h"

Tour::Tour(Couleur c, Nom n, string pos) : Piece(c,n,pos){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Tour::~Tour(){}
