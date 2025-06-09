#include "Image.h"
#include "SobelFilter.h"
#include "BrightnessContrast.h"
#include "GammaCorrection.h"
#include "MeanBlur.h"
#include "GaussianBlur.h"
#include "Drawing.h"
#include <iostream>
#include <cassert>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_image.pgm>" << std::endl;
        return 1;
    }

    Image img;
    if (!img.load(argv[1])) {
        std::cerr << "Error loading image: " << argv[1] << std::endl;
        return 1;
    }

    assert(!img.isEmpty());

    Image processed(img.width(), img.height());

    SobelFilter sobel;
    bool sobel_ok = sobel.process(img, processed);
    assert(sobel_ok);
    assert(processed.width() == img.width());
    assert(processed.height() == img.height());
    assert(!processed.isEmpty());
    processed.save("sobel_edges.pgm");

    BrightnessContrast bc(1.5f, 30.0f);
    bool bc_ok = bc.process(img, processed);
    assert(bc_ok);
    assert(processed.width() == img.width());
    assert(processed.height() == img.height());
    assert(!processed.isEmpty());
    processed.save("brightness_contrast.pgm");

    GammaCorrection gc(0.5f);
    bool gc_ok = gc.process(img, processed);
    assert(gc_ok);
    assert(processed.width() == img.width());
    assert(processed.height() == img.height());
    assert(!processed.isEmpty());
    processed.save("gamma_correction.pgm");

    MeanBlur meanBlur(5);
    bool mean_ok = meanBlur.process(img, processed);
    assert(mean_ok);
    assert(processed.width() == img.width());
    assert(processed.height() == img.height());
    assert(!processed.isEmpty());
    processed.save("mean_blur.pgm");

    GaussianBlur gaussianBlur(5, 1.0f);
    bool gauss_ok = gaussianBlur.process(img, processed);
    assert(gauss_ok);
    assert(processed.width() == img.width());
    assert(processed.height() == img.height());
    assert(!processed.isEmpty());
    processed.save("gaussian_blur.pgm");

    // Draw some shapes
    Image drawing = Image::zeros(img.width(), img.height());
    Drawing::drawCircle(drawing, Point(img.width()/2, img.height()/2), 50, 255);
    Drawing::drawRectangle(drawing, Rectangle(100, 100, 200, 150), 255);
    Drawing::drawLine(drawing, Point(0, 0), Point(img.width()-1, img.height()-1), 255);
    drawing.save("drawing.pgm");

    std::cout << "Processing complete. Check the output files." << std::endl;
    return 0;
} 
