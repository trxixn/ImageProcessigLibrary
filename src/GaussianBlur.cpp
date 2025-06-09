#include "GaussianBlur.h"
#include <cmath>

GaussianBlur::GaussianBlur(int kernelSize, float sigma) : ImageProcessing() {
    m_kernelSize = kernelSize;
    m_sigma = sigma;
    m_kernel = new float*[m_kernelSize];
    for (int i = 0; i < m_kernelSize; i++) {
        m_kernel[i] = new float[m_kernelSize];
    }

    float sum = 0.0f;
    int radius = m_kernelSize / 2;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            float value = std::exp(-(x * x + y * y) / (2 * m_sigma * m_sigma));
            m_kernel[y + radius][x + radius] = value;
            sum += value;
        }
    }

    for (int y = 0; y < m_kernelSize; y++) {
        for (int x = 0; x < m_kernelSize; x++) {
            m_kernel[y][x] /= sum;
        }
    }
}

GaussianBlur::~GaussianBlur() {
    for (int i = 0; i < m_kernelSize; i++) {
        delete[] m_kernel[i];
    }
    delete[] m_kernel;
}

bool GaussianBlur::process(const Image& input, Image& output) {
    if (input.isEmpty() || output.isEmpty()) {
        return false;
    }

    int radius = m_kernelSize / 2;
    for (unsigned int y = 0; y < input.height(); y++) {
        for (unsigned int x = 0; x < input.width(); x++) {
            float sum = 0.0f;
            for (int ky = -radius; ky <= radius; ky++) {
                for (int kx = -radius; kx <= radius; kx++) {
                    int px = x + kx;
                    int py = y + ky;
                    if (px >= 0 && px < static_cast<int>(input.width()) && py >= 0 && py < static_cast<int>(input.height())) {
                        sum += input.at(px, py) * m_kernel[ky + radius][kx + radius];
                    }
                }
            }
            output.at(x, y) = static_cast<unsigned char>(sum);
        }
    }

    return true;
} 