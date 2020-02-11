#include <iostream>
#include <string>
using namespace std;
#include "fonctions.h"

//Remarque : L'ouverture du fichier n'a fonctionné qu'avec le path complet sur ma machine, à modifier

int main(){

    string* turn1 = lectureFichier("/home/enzo/git/CompleteurNotation/fichier.txt","1");
    string* turn2 = lectureFichier("/home/enzo/git/CompleteurNotation/fichier.txt","2");
    cout << "Turn 1 : " << turn1[0] << " " << turn1[1] << endl;
    cout << "Turn 2 : " << turn2[0] << " " << turn2[1] << endl;
    return 0;

}