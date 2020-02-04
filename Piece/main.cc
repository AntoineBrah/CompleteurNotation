#include<iostream>
#include<string>
#include "Piece.h"
using namespace std;

int main(int argc, char const *argv[])
{
	Piece* p = new Piece(Noir, Roi);

	cout<<"Bonjour fdp "<<p->getCouleur()<<endl;

	delete p;

	return 0;
}