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

## Using as a Library

### Method 1: Include Source Files
The simplest way to use this library is to include the source files directly in your project:

1. Copy the `src` directory to your project
2. Add the following to your CMakeLists.txt:
```cmake
add_library(image_processing
    src/Image.cpp
    src/BrightnessContrast.cpp
    src/GammaCorrection.cpp
    src/Convolution.cpp
    src/Drawing.cpp
)

target_include_directories(image_processing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
```

3. Link it to your project:
```cmake
target_link_libraries(your_project PRIVATE image_processing)
```

4. Include the headers in your code:
```cpp
#include "Image.h"
#include "BrightnessContrast.h"
// ... other headers as needed
```

### Method 2: Build as Shared Library
To build and install as a shared library:

1. Build with shared library option:
```bash
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
```

2. In your project's CMakeLists.txt:
```cmake
find_package(image_processing REQUIRED)
target_link_libraries(your_project PRIVATE image_processing)
```

### Example Usage
```cpp
#include "Image.h"
#include "BrightnessContrast.h"

int main() {
    // Create and load an image
    Image img;
    img.load("input.pgm");
    
    // Create a processor
    BrightnessContrast processor(1.2f, 10.0f);
    
    // Process the image
    Image result;
    processor.process(img, result);
    
    // Save the result
    result.save("output.pgm");
    return 0;
}
```

### Creating Custom Processors
You can create your own image processors by inheriting from the `ImageProcessing` base class:

```cpp
#include "ImageProcessing.h"

class CustomProcessor : public ImageProcessing {
public:
    void process(const Image& src, Image& dst) override {
        // Your custom processing logic here
    }
};
```

## Test Images

For testing the library, you can use PGM (Portable Gray Map) files. A collection of test images is available at:
[FSU PGM Image Database](https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html)

Some recommended test images:
- `lena.pgm` (512x512) - Standard test image
- `baboon.pgm` (512x512) - Good for testing detail preservation
- `pepper.pgm` (256x256) - Good for testing contrast adjustments

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