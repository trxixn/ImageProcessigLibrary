#include "BrightnessContrast.h"
#include <algorithm>

BrightnessContrast::BrightnessContrast(float factor, float bias) : ImageProcessing() {
    m_factor = factor;
    m_bias = bias;
}

BrightnessContrast::~BrightnessContrast() {}

bool BrightnessContrast::process(const Image& input, Image& output) {
    if (input.isEmpty() || output.isEmpty()) {
        return false;
    }

    for (unsigned int y = 0; y < input.height(); y++) {
        for (unsigned int x = 0; x < input.width(); x++) {
            float pixel = input.at(x, y);
            pixel = pixel * m_factor + m_bias;
            pixel = std::max(0.0f, std::min(255.0f, pixel));
            output.at(x, y) = static_cast<unsigned char>(pixel);
        }
    }

    return true;
} 