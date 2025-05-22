# Image Processing Library

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard)
[![OpenCV](https://img.shields.io/badge/OpenCV-4.x-green.svg)](https://opencv.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A C++ library for image processing and analysis, providing a simple interface for common image manipulation tasks.

## Features

- **Basic Operations**
  - Image loading and saving
  - Region of Interest (ROI) extraction
  - Image arithmetic (addition, subtraction, multiplication)
  - Scalar operations

- **Image Processing**
  - Brightness and contrast adjustment
  - Gamma correction
  - Convolution with custom kernels
  - Image filtering

- **Drawing Functions**
  - Draw lines and circles
  - Draw rectangles
  - Custom color support

## Requirements

- C++17 or higher
- OpenCV 4.x
- CMake 3.10+
- A C++ compiler (GCC, Clang, or MSVC)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/image-processing.git
cd image-processing
```

2. Build the project:
```bash
mkdir build && cd build
cmake ..
make
```

## Usage

Here's a simple example showing how to adjust brightness and contrast:

```cpp
#include "Image.h"
#include "BrightnessContrast.h"

int main() {
    // Load an image
    Image img;
    img.load("input.jpg");
    
    // Adjust brightness and contrast
    BrightnessContrast processor(1.2f, 10.0f);  // alpha=1.2, beta=10
    Image result;
    processor.process(img, result);
    
    // Save the result
    result.save("output.jpg");
    return 0;
}
```

## API Overview

The library provides several key classes:

- `Image`: Core image class for basic operations
  - Loading and saving images
  - Pixel access and manipulation
  - ROI operations

- `ImageProcessing`: Base class for all processing operations
  - Virtual interface for image processing
  - Common processing pipeline

- `BrightnessContrast`: Brightness and contrast adjustment
  - Adjust image brightness
  - Modify image contrast
  - Combined operations

- `GammaCorrection`: Gamma correction
  - Adjust image gamma
  - Improve image visibility

- `Convolution`: Convolution operations
  - Apply custom kernels
  - Image filtering
  - Edge detection

- `Drawing`: Drawing functions
  - Draw basic shapes
  - Custom color support
  - Anti-aliasing support

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests.

## License

MIT License - see [LICENSE](LICENSE) file for details. 