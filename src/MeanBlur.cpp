#include "MeanBlur.h"

MeanBlur::MeanBlur(int kernelSize) : ImageProcessing() {
    m_kernelSize = kernelSize;
}

MeanBlur::~MeanBlur() {}

bool MeanBlur::process(const Image& input, Image& output) {
    if (input.isEmpty() || output.isEmpty()) {
        return false;
    }

    int radius = m_kernelSize / 2;
    for (unsigned int y = 0; y < input.height(); y++) {
        for (unsigned int x = 0; x < input.width(); x++) {
            float sum = 0.0f;
            int count = 0;
            for (int ky = -radius; ky <= radius; ky++) {
                for (int kx = -radius; kx <= radius; kx++) {
                    int px = x + kx;
                    int py = y + ky;
                    if (px >= 0 && px < static_cast<int>(input.width()) && py >= 0 && py < static_cast<int>(input.height())) {
                        sum += input.at(px, py);
                        count++;
                    }
                }
            }
            output.at(x, y) = static_cast<unsigned char>(sum / count);
        }
    }

    return true;
} 