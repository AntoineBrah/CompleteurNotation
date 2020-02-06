#include <iostream>
#include "Cellule.h"
#include "Pion.h"


int main(int argc, char* argv[]){


    
    /*Cellule *c = new Cellule(Noir, Roi);
    cout<<c->getPiece()->getNom()<<"bonjour"<<c->getPosition()<<endl;*/
    
    pion *P = new pion(Blanc,Pion);

    Cellule *c1 = new Cellule(P);

    cout<<c1->getPiece()->getNom()<<" "<<c1->getPiece()->getCouleur()<<" en "<<c1->getPosition()<<endl;


    


    return 0;
}