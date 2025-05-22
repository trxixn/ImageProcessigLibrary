#include "BrightnessContrast.h"
#include <algorithm>

using namespace std;

BrightnessContrast::BrightnessContrast(float alpha, float beta)
    : m_alpha(alpha), m_beta(beta) {}

void BrightnessContrast::process(const Image& src, Image& dst) {
    dst.release();
    dst = Image(src.width(), src.height());
    
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            float value = m_alpha * src.at(x, y) + m_beta;
            dst.at(x, y) = static_cast<unsigned char>(
                std::min(255.0f, std::max(0.0f, value)));
        }
    }
} 