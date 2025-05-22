#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "Point.h"
#include "Size.h"

struct Rectangle {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;

    /**
     * @brief Default constructor
     * Initializes rectangle to (0,0,0,0)
     */
    Rectangle() : x(0), y(0), width(0), height(0) {}

    /**
     * @brief Constructor with specified coordinates and dimensions
     * @param x X coordinate
     * @param y Y coordinate
     * @param w Width
     * @param h Height
     */
    Rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
        : x(x), y(y), width(w), height(h) {}

    /**
     * @brief Constructor from Point and Size
     * @param p Point containing x,y coordinates
     * @param s Size containing width and height
     */
    Rectangle(const Point& p, const Size& s)
        : x(p.x), y(p.y), width(s.width), height(s.height) {}

    /**
     * @brief Addition operator
     * @param other Rectangle to add
     * @return Resulting rectangle
     */
    Rectangle operator+(const Rectangle& other) const;

    /**
     * @brief Subtraction operator
     * @param other Rectangle to subtract
     * @return Resulting rectangle
     */
    Rectangle operator-(const Rectangle& other) const;

    /**
     * @brief Intersection operator
     * @param other Rectangle to intersect with
     * @return Intersection rectangle
     */
    Rectangle operator&(const Rectangle& other) const; // intersection

    /**
     * @brief Union operator
     * @param other Rectangle to union with
     * @return Union rectangle
     */
    Rectangle operator|(const Rectangle& other) const; // union

    /**
     * @brief Stream output operator
     * @param os Output stream
     * @param rect Rectangle to output
     * @return Output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);

    /**
     * @brief Stream input operator
     * @param is Input stream
     * @param rect Rectangle to read into
     * @return Input stream
     */
    friend std::istream& operator>>(std::istream& is, Rectangle& rect);
};

#endif // RECTANGLE_H 