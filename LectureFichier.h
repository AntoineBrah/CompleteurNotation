#ifndef LectureFichier_H
#define LectureFichier_H

#include <iostream>
#include <fstream> // Flux de lecture/écriture
#include <string>
#include <vector>
#include <regex>

using namespace std;

class lectureFichier{

    private:
        ifstream monFlux;
        string ligne;

        string cb; // Coup blanc
        vector<string> descriptionCb; // piece, colonne, ligne, deplacement, promotion, echec

        string cn; // Coup noir
        vector<string> descriptionCn; // piece, colonne, ligne, deplacement, promotion, echec

        bool estCorrectementOuvert;

    public:
        lectureFichier(string);

        void printLigne() const;
        int lireLigneSuivante();

        void traiterLigne();

        bool getEstCorrectementOuvert() const;
        string getCoupBlanc() const;
        string getCoupNoir() const;

        ~lectureFichier();
};


void detecterCoup(string, vector<string>&);

#endif