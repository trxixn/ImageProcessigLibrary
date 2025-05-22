#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "ImageProcessing.h"
#include <vector>

class Convolution : public ImageProcessing {
public:
    /**
     * @brief Constructor for convolution operation
     * @param kernel 2D kernel matrix for convolution
     */
    Convolution(const std::vector<std::vector<float>>& kernel);

    /**
     * @brief Process the image using convolution
     * @param src Source image
     * @param dst Destination image
     */
    void process(const Image& src, Image& dst) override;

private:
    std::vector<std::vector<float>> m_kernel;
    int m_kernelSize;
};

#endif // CONVOLUTION_H 