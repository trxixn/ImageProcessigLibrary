#ifndef SOBEL_FILTER_H
#define SOBEL_FILTER_H

#include "ImageProcessing.h"

class SobelFilter : public ImageProcessing {
public:
    SobelFilter();
    ~SobelFilter();
    bool process(const Image& input, Image& output) override;

private:
    float** m_kernel;
    float** m_verticalKernel;
    int m_kernelSize;
    float m_factor;
    float m_bias;
};

#endif // SOBEL_FILTER_H 