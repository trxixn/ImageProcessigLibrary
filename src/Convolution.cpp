#include "Convolution.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

Convolution::Convolution(const std::vector<std::vector<float>>& kernel)
    : m_kernel(kernel) {
    if (kernel.empty() || kernel.size() != kernel[0].size() || kernel.size() % 2 == 0)
        throw std::invalid_argument("Kernel must be a square matrix with odd dimensions");
    m_kernelSize = kernel.size();
}

void Convolution::process(const Image& src, Image& dst) {
    dst.release();
    dst = Image(src.width(), src.height());
    int offset = m_kernelSize / 2;

    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            float sum = 0.0f;
            
            for (int ky = -offset; ky <= offset; ++ky) {
                for (int kx = -offset; kx <= offset; ++kx) {
                    int srcX = x + kx;
                    int srcY = y + ky;
                    
                    // Handle border cases with zero padding
                    if (srcX >= 0 && srcX < static_cast<int>(src.width()) &&
                        srcY >= 0 && srcY < static_cast<int>(src.height())) {
                        sum += src.at(srcX, srcY) * 
                               m_kernel[ky + offset][kx + offset];
                    }
                }
            }
            
            dst.at(x, y) = static_cast<unsigned char>(
                std::min(255.0f, std::max(0.0f, sum)));
        }
    }
} 