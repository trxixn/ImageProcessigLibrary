#include "Point.h"
#include <iostream>

using namespace std;

std::ostream& operator<<(std::ostream& os, const Point& pt) {
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& pt) {
    char c;
    is >> c; // read '('
    is >> pt.x;
    is >> c; // read ','
    is >> pt.y;
    is >> c; // read ')'
    return is;
} 