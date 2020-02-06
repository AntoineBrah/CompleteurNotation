#include "Pion.h"

pion::pion() : Piece(){}

pion::pion(Couleur C, Nom N) : Piece(C,N){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}