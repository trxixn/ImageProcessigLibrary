#include "Image.h"
#include "BrightnessContrast.h"
#include "GammaCorrection.h"
#include "Convolution.h"
#include "Drawing.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_image.pgm>" << std::endl;
        return -1;
    }

    try {
        // Load image
        Image img;
        if (!img.load(argv[1])) {
            std::cerr << "Error: Could not load image " << argv[1] << std::endl;
            return -1;
        }
        std::cout << "Loaded image: " << img.width() << "x" << img.height() << std::endl;

        // Create a copy for processing
        Image processed = img;

        // Apply brightness and contrast
        BrightnessContrast bc(1.5f, 30.0f); // Increase contrast and brightness
        bc.process(img, processed);
        processed.save("brightness_contrast.pgm");

        // Apply gamma correction
        GammaCorrection gc(0.5f); // Darken the image
        gc.process(img, processed);
        processed.save("gamma_correction.pgm");

        // Apply mean blur
        std::vector<std::vector<float>> meanKernel = {
            {1.0f/9, 1.0f/9, 1.0f/9},
            {1.0f/9, 1.0f/9, 1.0f/9},
            {1.0f/9, 1.0f/9, 1.0f/9}
        };
        Convolution meanBlur(meanKernel);
        meanBlur.process(img, processed);
        processed.save("mean_blur.pgm");

        // Apply Gaussian blur
        std::vector<std::vector<float>> gaussianKernel = {
            {1.0f/16, 2.0f/16, 1.0f/16},
            {2.0f/16, 4.0f/16, 2.0f/16},
            {1.0f/16, 2.0f/16, 1.0f/16}
        };
        Convolution gaussianBlur(gaussianKernel);
        gaussianBlur.process(img, processed);
        processed.save("gaussian_blur.pgm");

        // Draw some shapes
        Image drawing = Image::zeros(img.width(), img.height());
        Drawing::drawCircle(drawing, Point(img.width()/2, img.height()/2), 50, 255);
        Drawing::drawRectangle(drawing, Rectangle(100, 100, 200, 150), 255);
        Drawing::drawLine(drawing, Point(0, 0), Point(img.width()-1, img.height()-1), 255);
        drawing.save("drawing.pgm");

        std::cout << "Processing complete. Check the output files." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
} 