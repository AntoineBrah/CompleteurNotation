#include "LectureFichier.h"

lectureFichier::lectureFichier(string fichier) : ligne(""), cb(""), cn(""), estCorrectementOuvert(false){

    monFlux.open(fichier.c_str()); // obligé de rajouter '.c_str()' car le constructeur de ifstream prend un 'const char*' et non pas un 'string' en paramètre.

    if(monFlux){
        cout << fichier << " : ouverture en lecture réussie." << endl;
        estCorrectementOuvert = true;
        getline(monFlux, ligne);
        traiterLigne();
    }
    else{
        cout << fichier << " : ouverture en lecture échouée." << endl;
    }
}

void lectureFichier::printLigne() const{
    cout << ligne << endl;
}

int lectureFichier::lireLigneSuivante(){
    if(getline(monFlux, ligne)){
        return 1;
    }
    else{
        return 0;
    }
}

bool lectureFichier::getEstCorrectementOuvert() const{
    return estCorrectementOuvert;
}

string lectureFichier::getCoupBlanc() const{
    return cb;
}

string lectureFichier::getCoupNoir() const{
    return cn;
}

void lectureFichier::traiterLigne(){
    string s;
    s = ligne;
    int pos = s.find_first_of(" ");
    cb = s.substr(0,pos);
    cn = s.substr(pos+1); // si on précise pas le deuxième paramètre, ça va jusqu'à la fin de la chaine
}

lectureFichier::~lectureFichier(){
    monFlux.close();
}




