#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "Image.h"

class ImageProcessing {
public:
    ImageProcessing() = default;
    /**
     * @brief Virtual destructor
     */
    virtual ~ImageProcessing() = default;

    /**
     * @brief Process the image
     * @param input Source image
     * @param output Destination image
     */
    virtual bool process(const Image& input, Image& output) = 0;
};

#endif // IMAGE_PROCESSING_H 