#include <iostream>
#include <cstdlib>
#include "Initialisation.h"

#define separator() cout << "---------------------------------" << endl


int main(int argc, char* argv[]){

    Piece *p1 = new Cavalier(Blanc, type::Cavalier, "b1");
    Cellule c1(p1);

    separator();
    cout << p1->toString() << endl;
    separator();
    cout << c1.toString() << endl;
    separator();

    p1->setPostion("a3");
    cout << p1->toString() << endl;
    separator();
    cout << c1.toString() << endl;
    separator();

    return 0;
}