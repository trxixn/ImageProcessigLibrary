#ifndef DRAWING_H
#define DRAWING_H

#include "Image.h"
#include "Point.h"
#include "Rectangle.h"

namespace Drawing {
    /**
     * @brief Draw a circle on the image
     * @param img Image to draw on
     * @param center Center point of the circle
     * @param radius Radius of the circle
     * @param color Color value to draw with
     */
    void drawCircle(Image& img, Point center, int radius, unsigned char color);

    /**
     * @brief Draw a line on the image
     * @param img Image to draw on
     * @param p1 Starting point of the line
     * @param p2 Ending point of the line
     * @param color Color value to draw with
     */
    void drawLine(Image& img, Point p1, Point p2, unsigned char color);

    /**
     * @brief Draw a rectangle on the image using Rectangle struct
     * @param img Image to draw on
     * @param rect Rectangle to draw
     * @param color Color value to draw with
     */
    void drawRectangle(Image& img, Rectangle rect, unsigned char color);

    /**
     * @brief Draw a rectangle on the image using two points
     * @param img Image to draw on
     * @param tl Top-left point of the rectangle
     * @param br Bottom-right point of the rectangle
     * @param color Color value to draw with
     */
    void drawRectangle(Image& img, Point tl, Point br, unsigned char color);
}

#endif // DRAWING_H 