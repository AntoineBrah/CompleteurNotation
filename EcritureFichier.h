#ifndef EcritureFichier_H
#define EcritureFichier_H

#include<iostream>
#include<fstream> // Flux de lecture/écriture
#include<string>

using namespace std;

class ecritureFichier{

    private:
        ofstream monFlux;

    public:
        ecritureFichier(string);
        ~ecritureFichier();

};

void viderFichier();
void correctionSyntaxe();

#endif