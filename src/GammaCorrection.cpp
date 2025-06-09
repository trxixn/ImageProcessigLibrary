#include "GammaCorrection.h"
#include <cmath>

GammaCorrection::GammaCorrection(float gamma) : ImageProcessing() {
    m_gamma = gamma;
}

GammaCorrection::~GammaCorrection() {}

bool GammaCorrection::process(const Image& input, Image& output) {
    if (input.isEmpty() || output.isEmpty()) {
        return false;
    }

    for (unsigned int y = 0; y < input.height(); y++) {
        for (unsigned int x = 0; x < input.width(); x++) {
            float pixel = input.at(x, y);
            pixel = std::pow(pixel / 255.0f, m_gamma) * 255.0f;
            output.at(x, y) = static_cast<unsigned char>(pixel);
        }
    }

    return true;
} 