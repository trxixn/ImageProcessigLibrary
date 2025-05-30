#include "BrightnessContrast.h"
#include <algorithm>

using namespace std;

BrightnessContrast::BrightnessContrast(float alpha, float beta)
    : m_alpha(alpha), m_beta(beta) {}

bool BrightnessContrast::process(const Image& src, Image& dst) {
    // Clear any existing data in the destination image
    dst.release();
    // Create a new empty image with same dimensions as source
    dst = Image(src.width(), src.height());

    // Process each pixel in the image
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            // Apply brightness/contrast formula:
            // new_value = alpha * original_value + beta
            // where:
            // - alpha (m_alpha) controls contrast (multiplier)
            // - beta (m_beta) controls brightness (offset)
            float value = m_alpha * src.at(x, y) + m_beta;
            
            // Clamp the value to valid range [0, 255] and convert to byte
            // This ensures the pixel value stays within valid grayscale range
            dst.at(x, y) = static_cast<unsigned char>(
                std::min(255.0f, std::max(0.0f, value)));
        }
    }
    return true;
} 