#ifndef LectureFichier_H
#define LectureFichier_H

#include<iostream>
#include<fstream> // Flux de lecture/écriture
#include<string>

using namespace std;

class lectureFichier{

    private:
        ifstream monFlux;
        string ligne;

        string cb;
        string cn;

    public:
        lectureFichier();

        void getLigne() const;
        int lireLigneSuivante();

        void traiter();
 
        string getCb() const;
        string getCn() const;

        //~lectureFichier();
};

#endif