#include <iostream>
#include <string>
using namespace std;
#include "Cavalier.h"

Cavalier::Cavalier() : Piece(){}

Cavalier::Cavalier(Couleur C, Nom N) : Piece(C,N){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Cavalier::~Cavalier(){}