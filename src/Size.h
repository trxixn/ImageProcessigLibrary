#ifndef SIZE_H
#define SIZE_H

class Size {
public:
    unsigned int width;
    unsigned int height;

    /**
     * @brief Default constructor
     * Initializes size to (0,0)
     */
    Size() : width(0), height(0) {}

    /**
     * @brief Constructor with specified dimensions
     * @param width Width of the size
     * @param height Height of the size
     */
    Size(unsigned int width, unsigned int height) 
        : width(width), height(height) {}
};

#endif // SIZE_H 