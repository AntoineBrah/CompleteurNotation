#ifndef Point_H
#define Point_H

#include <iostream>
#include "Position.h"

using namespace std;

class Point{

    private:
        int x;
        int y;
    public:
        Point(int,int);

        int getX() const;
        int getY() const;

        Point operator+(const Point&) const;
        void operator+=(const Point&);
        ostream& affiche(ostream& os) const;
};

ostream& operator<<(ostream& os, const Point &p);

Point convertPositionToPoint(Position);
string convertPointToPosition(Point);

#endif