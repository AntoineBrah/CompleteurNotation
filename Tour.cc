#include <iostream>
#include <string>
using namespace std;
#include "Tour.h"

Tour::Tour() : Piece(){}

Tour::Tour(Couleur C, Nom N) : Piece(C,N){
	switch(couleur){
		case Blanc : skin = '/';
		case Noir : skin = '#';
	}
}

Tour::~Tour(){}
