#ifndef GAMMA_CORRECTION_H
#define GAMMA_CORRECTION_H

#include "ImageProcessing.h"

class GammaCorrection : public ImageProcessing {
public:
    /**
     * @brief Constructor for gamma correction
     * @param gamma Gamma value (gamma > 0)
     */
    GammaCorrection(float gamma);

    /**
     * @brief Process the image using gamma correction
     * @param src Source image
     * @param dst Destination image
     */
    void process(const Image& src, Image& dst) override;

private:
    float m_gamma;
};

#endif // GAMMA_CORRECTION_H 