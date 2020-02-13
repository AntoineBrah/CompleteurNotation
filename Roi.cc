#include <iostream>
#include <string>
using namespace std;
#include "Roi.h"

Roi::Roi() : Piece(){}

Roi::Roi(Couleur C, Nom N) : Piece(C,N){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Roi::~Roi(){}