#include <iostream>
#include <string>
using namespace std;
#include "Fou.h"

Fou::Fou() : Piece(){}

Fou::Fou(Couleur C, Nom N) : Piece(C,N){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Fou::~Fou(){}