#include "Rectangle.h"
#include <iostream>
#include <algorithm>

using namespace std;

Rectangle Rectangle::operator+(const Rectangle& other) const {
    return Rectangle(x + other.x, y + other.y, width + other.width, height + other.height);
}

Rectangle Rectangle::operator-(const Rectangle& other) const {
    return Rectangle(x - other.x, y - other.y, width - other.width, height - other.height);
}

Rectangle Rectangle::operator&(const Rectangle& other) const {
    int x1 = std::max(x, other.x);
    int y1 = std::max(y, other.y);
    int x2 = std::min(x + width, other.x + other.width);
    int y2 = std::min(y + height, other.y + other.height);
    
    if (x2 <= x1 || y2 <= y1)
        return Rectangle(0, 0, 0, 0);
        
    return Rectangle(x1, y1, x2 - x1, y2 - y1);
}

Rectangle Rectangle::operator|(const Rectangle& other) const {
    int x1 = std::min(x, other.x);
    int y1 = std::min(y, other.y);
    int x2 = std::max(x + width, other.x + other.width);
    int y2 = std::max(y + height, other.y + other.height);
    
    return Rectangle(x1, y1, x2 - x1, y2 - y1);
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
    os << "Rectangle(" << rect.x << ", " << rect.y << ", " 
       << rect.width << ", " << rect.height << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& rect) {
    is >> rect.x >> rect.y >> rect.width >> rect.height;
    return is;
} 