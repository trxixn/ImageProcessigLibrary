#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#include "ImageProcessing.h"

class GaussianBlur : public ImageProcessing {
public:
    GaussianBlur(int kernelSize, float sigma);
    ~GaussianBlur();
    bool process(const Image& input, Image& output) override;

private:
    float** m_kernel;
    int m_kernelSize;
    float m_sigma;
};

#endif // GAUSSIAN_BLUR_H 