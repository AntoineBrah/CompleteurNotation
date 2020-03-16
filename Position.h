#ifndef Position_H
#define Position_H

#include <iostream>
#include <string>
#include "Couleur.h"

using namespace std;

class Position{

    private:
        string colonne;
        string ligne;

        Couleur couleurCase;
    public:
        Position();
        Position(string);

        void setCoord(string);

        string getCoord() const;
        string getCouleur() const;
        string getColonne() const;
        string getLigne() const;
        string toString() const;
    
};

#endif