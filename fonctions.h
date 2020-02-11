#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string* lectureFichier(string path, string coup){

    string const thisPath(path);
    ifstream fichier(thisPath);
    if(fichier){
        string test;
        string numCoup = coup + '.';
        while (test != numCoup){
            fichier >> test;
        }
        string coupBlanc, coupNoir;
        fichier >> coupBlanc;
        fichier >> coupNoir;
        //cout << coupBlanc << endl;
        //cout << coupNoir << endl;
        string* turn = new string[2];
        turn[0] = coupBlanc;
        turn[1] = coupNoir;
        return turn;
    }
    else{
        cout << "erreur lors de l'ouverture du fichier" << endl;
        string* erreur = new string[2];
        erreur[0] = "-1";
        erreur[1] = "-1";
        return erreur;
    }

}