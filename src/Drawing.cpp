#include "Drawing.h"
#include <cmath>
#include <algorithm>

using namespace std;

namespace Drawing {

void drawCircle(Image& img, Point center, int radius, unsigned char color) {
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x*x + y*y <= radius*radius) {
                int imgX = center.x + x;
                int imgY = center.y + y;
                if (imgX >= 0 && imgX < static_cast<int>(img.width()) &&
                    imgY >= 0 && imgY < static_cast<int>(img.height())) {
                    img.at(imgX, imgY) = color;
                }
            }
        }
    }
}

void drawLine(Image& img, Point p1, Point p2, unsigned char color) {
    int dx = std::abs(p2.x - p1.x);
    int dy = std::abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (p1.x >= 0 && p1.x < static_cast<int>(img.width()) &&
            p1.y >= 0 && p1.y < static_cast<int>(img.height())) {
            img.at(p1.x, p1.y) = color;
        }

        if (p1.x == p2.x && p1.y == p2.y) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            p1.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            p1.y += sy;
        }
    }
}

void drawRectangle(Image& img, Rectangle rect, unsigned char color) {
    Point tl(rect.x, rect.y);
    Point br(rect.x + rect.width - 1, rect.y + rect.height - 1);
    drawRectangle(img, tl, br, color);
}

void drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
    Point tr(br.x, tl.y);
    Point bl(tl.x, br.y);
    
    drawLine(img, tl, tr, color);
    drawLine(img, tr, br, color);
    drawLine(img, br, bl, color);
    drawLine(img, bl, tl, color);
}

} // namespace Drawing 