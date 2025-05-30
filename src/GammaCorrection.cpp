#include "GammaCorrection.h"
#include <cmath>
#include <algorithm>

using namespace std;

// Constructor takes gamma value (typically between 0.1 and 3.0)
// gamma < 1.0 makes image brighter
// gamma > 1.0 makes image darker
GammaCorrection::GammaCorrection(float gamma) : m_gamma(gamma) {}

bool GammaCorrection::process(const Image& src, Image& dst) {
    // Clear destination image and create new one with same size
    dst.release();
    dst = Image(src.width(), src.height());
    
    // Process each pixel in the image
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            // Gamma correction formula:
            // output = 255 * (input/255)^gamma
            // This creates a non-linear adjustment to brightness
            float value = std::pow(src.at(x, y) / 255.0f, m_gamma) * 255.0f;
            
            // Clamp the result to valid range [0, 255] and convert to byte
            dst.at(x, y) = static_cast<unsigned char>(
                std::min(255.0f, std::max(0.0f, value)));
        }
    }
    return true;
} 