#include "Point.h"

Point::Point(): x(0), y(0){}
Point::Point(int x, int y) : x(x), y(y){}

Point::Point(const Point &p) : x(p.getX()), y(p.getY()){}

Point& Point::operator=(const Point &p){

    if(&p != this){
        x = p.getX();
        y = p.getY();
    }

    return *this;

}

Point Point::operator+(const Point &p) const{
    Point p2(*this);
    p2.x += p.x;
    p2.y += p.y;
    return p2;
}

Point Point::operator-(const Point &p) const{
    Point p2(*this);
    p2.x -= p.x;
    p2.y -= p.y;
    return p2;
}

void Point::operator+=(const Point& p){
    x += p.getX();
    y += p.getY();
}

int Point::getX() const{
    return x;
}

int Point::getY() const{
    return y;
}

void Point::setX(int a){
    x = a;
}

void Point::setY(int a){
    y = a;
}


void Point::setCoordNulles(){
    x = 0;
    y = 0;
}

ostream& Point::affiche(ostream& os) const{
    return os << "(" << x << "," << y << ")";
}

bool estCorrectPoint(const Point &p){
    return p.getX()>=1 && p.getX()<=8 && p.getY()>=1 && p.getY()<=8;
}

ostream& operator<<(ostream& os, const Point &p){
    return p.affiche(os);
}


/* 
* Attention car une position s'écrit de la forme [colonne][ligne]
* alors qu'un point s'écrit de la forme (x,y) ou x désigne une ligne
* et y une colonne.
*/ 

Point convertPositionToPoint(Position pos){
    string pos2 = pos.getCoord();

    int x;

    switch(pos2[1]){
        case '1':
            x = 1;
            break;
        case '2':
            x = 2;
            break;
        case '3':
            x = 3;
            break;
        case '4':
            x = 4;
            break;
        case '5':
            x = 5;
            break;
        case '6':
            x = 6;
            break;
        case '7':
            x = 7;
            break;
        case '8':
            x = 8;
            break;
        default:
            cout << "*Il faudra gérer le fait qu'un utilisateur déplace une pièce en dehors de l'échiquier (ligne)" << endl;
            break;
    }

    int y;

    switch(pos2[0]){
        case 'a':
            y = 1;
            break;
        case 'b':
            y = 2;
            break;
        case 'c':
            y = 3;
            break;
        case 'd':
            y = 4;
            break;
        case 'e':
            y = 5;
            break;
        case 'f':
            y = 6;
            break;
        case 'g':
            y = 7;
            break;
        case 'h':
            y = 8;
            break;
        default:
            cout << "*Il faudra gérer le fait qu'un utilisateur déplace une pièce en dehors de l'échiquier (colonne)" << endl;
            break;
    }

    Point p(x,y);

    return p;
}

string convertPointToPosition(Point p){
    
    string colonne;

    switch(p.getY()){
        case 1:
            colonne = "a";
            break;
        case 2:
            colonne = "b";
            break;
        case 3:
            colonne = "c";
            break;
        case 4:
            colonne = "d";
            break;
        case 5:
            colonne = "e";
            break;
        case 6:
            colonne = "f";
            break;
        case 7:
            colonne = "g";
            break;
        case 8:
            colonne = "h";
            break;
        default:
            cout << "Il faudra gérer le fait qu'un utilisateur déplace une pièce en dehors de l'échiquier (colonne) [ici : " << p.getY() << endl;
            break;
    }

    string ligne;

    switch(p.getX()){
        case 1:
            ligne = "1";
            break;
        case 2:
            ligne = "2";
            break;
        case 3:
            ligne = "3";
            break;
        case 4:
            ligne = "4";
            break;
        case 5:
            ligne = "5";
            break;
        case 6:
            ligne = "6";
            break;
        case 7:
            ligne = "7";
            break;
        case 8:
            ligne = "8";
            break;
        default:
            cout << "Il faudra gérer le fait qu'un utilisateur déplace une pièce en dehors de l'échiquier (ligne)" << endl;
            cout << "ici : " << p.getX() << endl;
            break;
    }

    string position = colonne+ligne;

    return position;
}