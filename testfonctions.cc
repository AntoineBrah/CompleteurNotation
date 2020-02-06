#include <iostream>
#include <string>
using namespace std;
#include "fonctions.h"

//Remarque : L'ouverture du fichier n'a fonctionné qu'avec le path complet sur ma machine, à modifier

int main(){

    lectureFichier("/home/enzo/git/CompleteurNotation/fichier.txt",1);
    lectureFichier("/home/enzo/git/CompleteurNotation/fichier.txt",2);
    return 0;

}