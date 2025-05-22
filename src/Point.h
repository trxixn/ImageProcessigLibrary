#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    int x, y;

    /**
     * @brief Default constructor
     * Initializes point coordinates to (0,0)
     */
    Point() : x(0), y(0) {}

    /**
     * @brief Constructor with specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     */
    Point(int x, int y) : x(x), y(y) {}

    /**
     * @brief Stream output operator
     * @param os Output stream
     * @param pt Point to output
     * @return Output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Point& pt);

    /**
     * @brief Stream input operator
     * @param is Input stream
     * @param pt Point to read into
     * @return Input stream
     */
    friend std::istream& operator>>(std::istream& is, Point& pt);
};

#endif // POINT_H 