#include <iostream>
#include <string>
using namespace std;
#include "Dame.h"

Dame::Dame() : Piece(){}

Dame::Dame(Couleur C, Nom N) : Piece(C,N){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Dame::~Dame(){}