#include "GammaCorrection.h"
#include <cmath>
#include <algorithm>

using namespace std;

GammaCorrection::GammaCorrection(float gamma) : m_gamma(gamma) {}

void GammaCorrection::process(const Image& src, Image& dst) {
    dst.release();
    dst = Image(src.width(), src.height());
    
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            float value = std::pow(src.at(x, y) / 255.0f, m_gamma) * 255.0f;
            dst.at(x, y) = static_cast<unsigned char>(
                std::min(255.0f, std::max(0.0f, value)));
        }
    }
} 