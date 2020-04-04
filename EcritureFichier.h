#ifndef EcritureFichier_H
#define EcritureFichier_H

#include<iostream>
#include<fstream> // Flux de lecture/écriture
#include<string>

using namespace std;

class ecritureFichier{

    private:
        ofstream monFlux;
        string path; // Chemin du fichier

    public:
        ecritureFichier(const string p, string contenu);
        string getPath() const;
        ~ecritureFichier();

};

void viderFichier(const string);
void correctionSyntaxe(const string);

#endif