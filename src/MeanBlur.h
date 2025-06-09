#ifndef MEAN_BLUR_H
#define MEAN_BLUR_H

#include "ImageProcessing.h"

class MeanBlur : public ImageProcessing {
public:
    MeanBlur(int kernelSize);
    ~MeanBlur();
    bool process(const Image& input, Image& output) override;

private:
    int m_kernelSize;
};

#endif // MEAN_BLUR_H 