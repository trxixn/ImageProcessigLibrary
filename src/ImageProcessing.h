#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "Image.h"

class ImageProcessing {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~ImageProcessing() = default;

    /**
     * @brief Process the image
     * @param src Source image
     * @param dst Destination image
     */
    virtual void process(const Image& src, Image& dst) = 0;
};

#endif // IMAGE_PROCESSING_H 