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

        string cb; // Coup blanc
        string cn; // Coup noir

    public:
        lectureFichier(string);

        void getLigne() const;
        int lireLigneSuivante();

        void traiter();
 
        string getCoupBlanc() const;
        string getCoupNoir() const;

        ~lectureFichier();
};

#endif