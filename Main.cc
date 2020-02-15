#include <iostream>
#include "Position.h"
#include <typeinfo>


int main(int argc, char* argv[]){
    
    Position p1("a9");
    Position p2("i4");
    Position p3("b6");

    cout << p3.toString() << endl;


    return 0;
}