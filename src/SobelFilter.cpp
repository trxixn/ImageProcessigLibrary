#include "SobelFilter.h"
#include <cmath>

SobelFilter::SobelFilter() : ImageProcessing() {
    m_kernelSize = 3;
    m_kernel = new float*[m_kernelSize];
    m_verticalKernel = new float*[m_kernelSize];
    for (int i = 0; i < m_kernelSize; i++) {
        m_kernel[i] = new float[m_kernelSize];
        m_verticalKernel[i] = new float[m_kernelSize];
    }

    m_kernel[0][0] = -1; m_kernel[0][1] = 0; m_kernel[0][2] = 1;
    m_kernel[1][0] = -2; m_kernel[1][1] = 0; m_kernel[1][2] = 2;
    m_kernel[2][0] = -1; m_kernel[2][1] = 0; m_kernel[2][2] = 1;

    m_verticalKernel[0][0] = -1; m_verticalKernel[0][1] = -2; m_verticalKernel[0][2] = -1;
    m_verticalKernel[1][0] = 0;  m_verticalKernel[1][1] = 0;  m_verticalKernel[1][2] = 0;
    m_verticalKernel[2][0] = 1;  m_verticalKernel[2][1] = 2;  m_verticalKernel[2][2] = 1;

    m_factor = 1.0f;
    m_bias = 0.0f;
}

SobelFilter::~SobelFilter() {
    for (int i = 0; i < m_kernelSize; i++) {
        delete[] m_kernel[i];
        delete[] m_verticalKernel[i];
    }
    delete[] m_kernel;
    delete[] m_verticalKernel;
}

bool SobelFilter::process(const Image& input, Image& output) {
    if (input.isEmpty() || output.isEmpty()) {
        return false;
    }

    Image horizontalEdges(input.width(), input.height());
    Image verticalEdges(input.width(), input.height());

    for (unsigned int y = 0; y < input.height(); y++) {
        for (unsigned int x = 0; x < input.width(); x++) {
            float sum = 0.0f;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int px = x + kx;
                    int py = y + ky;
                    if (px >= 0 && px < static_cast<int>(input.width()) && py >= 0 && py < static_cast<int>(input.height())) {
                        sum += input.at(px, py) * m_kernel[ky + 1][kx + 1];
                    }
                }
            }
            horizontalEdges.at(x, y) = static_cast<unsigned char>(std::abs(sum));
        }
    }

    for (unsigned int y = 0; y < input.height(); y++) {
        for (unsigned int x = 0; x < input.width(); x++) {
            float sum = 0.0f;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int px = x + kx;
                    int py = y + ky;
                    if (px >= 0 && px < static_cast<int>(input.width()) && py >= 0 && py < static_cast<int>(input.height())) {
                        sum += input.at(px, py) * m_verticalKernel[ky + 1][kx + 1];
                    }
                }
            }
            verticalEdges.at(x, y) = static_cast<unsigned char>(std::abs(sum));
        }
    }

    for (unsigned int y = 0; y < input.height(); y++) {
        for (unsigned int x = 0; x < input.width(); x++) {
            float h = horizontalEdges.at(x, y);
            float v = verticalEdges.at(x, y);
            float magnitude = std::sqrt(h * h + v * v);
            output.at(x, y) = static_cast<unsigned char>(magnitude);
        }
    }

    return true;
} 