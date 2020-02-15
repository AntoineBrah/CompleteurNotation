#include "LectureFichier.h"

lectureFichier::lectureFichier() : ligne(""), cb(""), cn(""){

    string cheminFichier;

    cin >> cheminFichier;

    monFlux.open(cheminFichier.c_str()); // obligé de rajouter '.c_str()' car le constructeur de ifstream prend un 'const char*' et non pas un 'string' en paramètre.

    if(monFlux){
        cout << cheminFichier << " : ouverture en lecture réussie." << endl;
        getline(monFlux, ligne);
    }
    else{
        cout << cheminFichier << " : ouverture en lecture échouée." << endl;
    }
}

void lectureFichier::getLigne() const{
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

string lectureFichier::getCb() const{
    return cb;
}

string lectureFichier::getCn() const{
    return cn;
}

void lectureFichier::traiter(){
    string s;
    s = ligne;
    int pos = s.find_first_of(" ");
    cb = s.substr(0,pos);
    cn = s.substr(pos+1);
}

lectureFichier::~lectureFichier(){
    monFlux.close();
}



