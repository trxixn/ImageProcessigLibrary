#ifndef BRIGHTNESS_CONTRAST_H
#define BRIGHTNESS_CONTRAST_H

#include "ImageProcessing.h"

class BrightnessContrast : public ImageProcessing {
public:
    /**
     * @brief Constructor for brightness and contrast adjustment
     * @param factor Contrast factor (factor > 0)
     * @param bias Brightness factor
     */
    BrightnessContrast(float factor, float bias);

    /**
     * @brief Process the image to adjust brightness and contrast
     * @param input Source image
     * @param output Destination image
     */
    bool process(const Image& input, Image& output) override;

    ~BrightnessContrast();

private:
    float m_factor; // contrast
    float m_bias;   // brightness
};

#endif // BRIGHTNESS_CONTRAST_H 