#include <iostream>
#include "Cellule.h"


int main(int argc, char* argv[]){


    
    Cellule *c = new Cellule(Noir, Roi);
    cout<<c->getPiece()->getNom()<<"bonjour"<<c->getPosition()<<endl;
    


    return 0;
}