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

bool Convolution::process(const Image& src, Image& dst) {
    // Clear destination image and create new one with same size
    dst.release();
    dst = Image(src.width(), src.height());
    
    // Calculate how far to look around each pixel
    // For a 3x3 kernel, offset = 1 (look 1 pixel in each direction)
    // For a 5x5 kernel, offset = 2 (look 2 pixels in each direction)
    int offset = m_kernelSize / 2;

    // Process each pixel in the image
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            // Initialize sum for this pixel's convolution
            float sum = 0.0f;
            
            // Look at surrounding pixels based on kernel size
            // For each pixel, we look at a window of pixels around it
            for (int ky = -offset; ky <= offset; ++ky) {
                for (int kx = -offset; kx <= offset; ++kx) {
                    // Calculate position of the pixel we're looking at
                    int srcX = x + kx;
                    int srcY = y + ky;
                    
                    // Only process if the pixel is within image bounds
                    // This handles the edges of the image
                    if (srcX >= 0 && srcX < static_cast<int>(src.width()) &&
                        srcY >= 0 && srcY < static_cast<int>(src.height())) {
                        // Multiply the pixel value by the corresponding kernel value
                        // and add to the sum
                        sum += src.at(srcX, srcY) * 
                               m_kernel[ky + offset][kx + offset];
                    }
                }
            }
            
            // Clamp the result to valid range [0, 255] and convert to byte
            dst.at(x, y) = static_cast<unsigned char>(
                std::min(255.0f, std::max(0.0f, sum)));
        }
    }
    return true;
} 