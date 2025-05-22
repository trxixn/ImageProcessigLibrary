#ifndef BRIGHTNESS_CONTRAST_H
#define BRIGHTNESS_CONTRAST_H

#include "ImageProcessing.h"

class BrightnessContrast : public ImageProcessing {
public:
    /**
     * @brief Constructor for brightness and contrast adjustment
     * @param alpha Contrast factor (alpha > 0)
     * @param beta Brightness factor
     */
    BrightnessContrast(float alpha, float beta);

    /**
     * @brief Process the image to adjust brightness and contrast
     * @param src Source image
     * @param dst Destination image
     */
    void process(const Image& src, Image& dst) override;

private:
    float m_alpha; // contrast
    float m_beta;  // brightness
};

#endif // BRIGHTNESS_CONTRAST_H 